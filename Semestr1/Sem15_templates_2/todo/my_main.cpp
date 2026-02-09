#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <type_traits>
#include <utility>

// void Print() [with T = EN]
//  void PrintE() [with auto V = TWO]
//  void PrintE() [with auto V = THREE]
//  void PrintE() [with auto V = (EN)3]

static constexpr size_t kEnunNamePrefixLen =
    sizeof("constexpr std::string_view GetEnumNameImpl() [with T = ") - 1;
static constexpr size_t kEnunNameSuffixLen =
    sizeof("; std::string_view = std::basic_string_view<char>]") - 1;

template <typename T>
constexpr std::string_view GetEnumNameImpl() {
    std::string_view name = __PRETTY_FUNCTION__;
    name = name.substr(kEnunNamePrefixLen, name.size() - kEnunNameSuffixLen);
    // name.remove_prefix(kEnunNamePrefixLen);
    // name.remove_suffix(kEnunNameSuffixLen);
    return name;
}

static constexpr size_t kEnunValueNamePrefixLen =
    sizeof(
        "constexpr std::string_view GetEnumValueNameImpl() [with auto V = ") -
    1;
static constexpr size_t kEnunValueNameSuffixLen =
    sizeof("; std::string_view = std::basic_string_view<char>]") - 1;

template <auto V>
constexpr std::string_view GetEnumValueNameImpl() {
    std::string_view name = __PRETTY_FUNCTION__;
    name = name.substr(
        kEnunValueNamePrefixLen, name.size() - kEnunValueNameSuffixLen);
    // name.remove_prefix(kEnunValueNamePrefixLen);
    // name.remove_suffix(kEnunValueNameSuffixLen);
    return name;
}

////////////////////////////////////////////////////////////////////////////////

template <typename Enum, int64_t MinLimit, int64_t LimitLen, int64_t... IntVals>
constexpr std::array<std::string_view, LimitLen> CreateArrayImpl(
    std::integer_sequence<int64_t, IntVals...>) {
    return {GetEnumValueNameImpl<static_cast<Enum>(IntVals + MinLimit)>()...};
}

template <typename Enum, int64_t MinLimit, int64_t LimitLen>
constexpr std::array<std::string_view, LimitLen> CreateArray() {
    return CreateArrayImpl<Enum, MinLimit, LimitLen>(
        std::make_integer_sequence<int64_t, LimitLen>{});
}

////////////////////////////////////////////////////////////////////////////////

template <size_t N, size_t... Vals>
constexpr std::array<size_t, N> CreateIndexArrayImpl(
    std::index_sequence<Vals...>) {
    return {Vals...};
}

template <size_t N>
constexpr std::array<size_t, N> CreateIndexArray() {
    return CreateIndexArrayImpl<N>(std::make_index_sequence<N>{});
}

template <class Enum, std::size_t MaxN = 512>
    requires std::is_enum_v<Enum>
struct EnumeratorTraits {
  public:
    using UnderlineType = std::underlying_type_t<Enum>;
    [[maybe_unused]] static constexpr std::string_view kEnumName =
        GetEnumNameImpl<Enum>();

    static constexpr int64_t kSignedMaxN = static_cast<int64_t>(MaxN);
    static constexpr int64_t kTypeMin =
        std::numeric_limits<UnderlineType>::min();
    static constexpr int64_t kTypeMax =
        std::numeric_limits<UnderlineType>::max();

    static constexpr int64_t kMinLimit = std::max(kTypeMin, -kSignedMaxN);
    static constexpr int64_t kMaxLimit = std::min(kTypeMax, kSignedMaxN);

    static constexpr int64_t kLimitLen =
        kMaxLimit - kMinLimit + 1;  // +1 for 0 index

    template <typename T>
    using Array = std::array<T, kLimitLen>;

    struct DataImpl {
        size_t enum_size = 0;
        Array<int64_t> indexes{};
    };

    static constexpr DataImpl CreateDataImpl() {
        DataImpl data;

        Array<std::string_view> all_names_arr =
            CreateArray<Enum, kMinLimit, kLimitLen>();
        for (int64_t i = 0; i < kLimitLen; ++i) {
            // std::cout << all_names_arr[i] << '\n';
            if (!all_names_arr[i].starts_with('(')) {
                data.indexes[data.enum_size] = i - kMinLimit;
                ++data.enum_size;
            }
        }
        return data;
    }

    inline static constexpr DataImpl kDataImpl = CreateDataImpl();

  public:
    static constexpr std::size_t size() noexcept { return kDataImpl.enum_size; }

    static constexpr Enum at(std::size_t i) noexcept {
        return Enum(kDataImpl.indexes[i]);
    }

    static constexpr std::string_view nameAt(std::size_t i) noexcept {
        return GetEnumValueNameImpl<at(i)>();
    }

  private:
    // static constexpr Array<int64_t> kIndices = SizeArrImpl();
    // static constexpr std::size_t kCount = SizeImpl();
};

enum EN {
    ONE,
    TWO,
    THREE,
};

enum class Shape {  // : int
    SQUARE = 1,
    CIRCLE = 5,
    LINE = -1,
    POINT = -2
};

// check compile time capabilities
// static_assert(EnumeratorTraits<Shape>::size() == 4);
static_assert(EnumeratorTraits<Shape>::size() == 3);
// static_assert(EnumeratorTraits<Shape>::nameAt(0) == "POINT");
// static_assert(EnumeratorTraits<Shape>::at(0) == Shape::POINT);
// static_assert(EnumeratorTraits<Shape>::at(1) == Shape::SQUARE);
// static_assert(EnumeratorTraits<Shape>::at(3) == Shape::LINE);

template <typename T>
void Foo() = delete;

int main() {
    //   std::cout << GetEnumNameImpl<EN>() << '\n';
    //   std::cout << GetEnumValueNameImpl<EN(1)>() << '\n';
    //   std::cout << GetEnumValueNameImpl<EN(2)>() << '\n';
    //   std::cout << GetEnumValueNameImpl<EN(3)>() << '\n';

    // std::cout << GetEnumNameImpl<Shape>() << '\n';
    // std::cout << GetEnumValueNameImpl<Shape(1)>() << '\n';
    // std::cout << GetEnumValueNameImpl<Shape(2)>() << '\n';
    // std::cout << GetEnumValueNameImpl<Shape(5)>() << '\n';

    // size_t count = 0;
    // std::array<std::string_view, 3> all_names_arr = CreateArray<EN, 0, 3>();
    // std::array<int64_t, 11> res;
    // std::cout << "=====Arr names=====\n";
    // for (int64_t i = 0; i < 5 * 2 + 1; ++i) {
    //   std::cout << all_names_arr[i] << '\n';
    //   if (!all_names_arr[i].starts_with('(')) {
    //     // res[count] = i - kSignedMaxN;
    //     ++count;
    //   }
    // }
    // std::cout << count << '\n';
    // std::cout << EnumeratorTraits<Shape>::size() << '\n';

    // std::cout << "=====Arr indexes=====\n";
    //   using UnderlineType = std::underlying_type_t<EN>;
    //   Foo<UnderlineType>();
    // static constexpr size_t MaxN = 512;
    // static constexpr int64_t kSignedMaxN = static_cast<int64_t>(MaxN);
    // static constexpr int64_t kTypeMin =
    // std::numeric_limits<UnderlineType>::min(); static constexpr int64_t
    // kTypeMax = std::numeric_limits<UnderlineType>::max();

    // static constexpr int64_t kMinLimit = std::max(kTypeMin, -kSignedMaxN);
    // static constexpr int64_t kMaxLimit = std::min(kTypeMax, kSignedMaxN);
    // EnumeratorTraits<Shape>::CreateDataImpl();

    // std::cout << EnumeratorTraits<Shape>::kMinLimit << '\n';
    // std::cout << EnumeratorTraits<Shape>::kMaxLimit << '\n';
    // static constexpr int64_t kArgCount = 5;
    // auto arr = CreateIndexArray<size_t(kArgCount) * 2 + 1>();
    // std::array<std::string_view, size_t(kArgCount)> res;
    // for (int64_t i = -kArgCount; i <= kArgCount; ++i) {
    //   res[i + kArgCount] = GetEnumValueNameImpl<Shape(i)>();
    //   std::cout << res[i + kArgCount] << '\n';
    // }

    // return count;
    // PrintE<EN(1)>();
    // PrintE<EN(2)>();
    // PrintE<EN(3)>();
}
