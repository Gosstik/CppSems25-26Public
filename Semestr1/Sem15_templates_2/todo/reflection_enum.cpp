#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <type_traits>
#include <utility>

constexpr void ExtractName(std::string_view& name) {
    size_t prefix_len = name.find('=') + 2;

#if defined(__clang__)  // clang++
    size_t suffix_begin = name.find(']', prefix_len);
#elif defined(__GNUC__) || defined(__GNUG__)  // g++
    size_t suffix_begin = name.find(';', prefix_len);
#elif defined(_MSC_VER)                       // MSVC
    static_assert(false, "MSVC is not supported");
#else
    static_assert(false, "Unsupported compiler");
#endif

    name = name.substr(prefix_len, suffix_begin - prefix_len);
}

template <typename T>
constexpr std::string_view GetEnumNameImpl() {
    std::string_view name = __PRETTY_FUNCTION__;
    ExtractName(name);
    return name;
}

template <auto V>
constexpr std::string_view GetEnumValueNameImpl() {
    std::string_view name = __PRETTY_FUNCTION__;
    ExtractName(name);
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
    static constexpr std::string_view kEnumName = GetEnumNameImpl<Enum>();

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
        Array<int64_t> vals{};
        Array<std::string_view> names_arr{};
    };

    static constexpr DataImpl CreateDataImpl() {
        DataImpl data{
            .names_arr = CreateArray<Enum, kMinLimit, kLimitLen>(),
        };

        for (int64_t i = 0; i < kLimitLen; ++i) {
            if (!data.names_arr[i].starts_with('(')) {
                size_t colon_pos = data.names_arr[i].find(':');
                if (colon_pos != std::string_view::npos) {
                    data.names_arr[i].remove_prefix(colon_pos + 2);
                }
                data.indexes[data.enum_size] = i;
                data.vals[data.enum_size] = i + kMinLimit;
                ++data.enum_size;
            }
        }
        return data;
    }

    inline static constexpr DataImpl kDataImpl = CreateDataImpl();

  public:
    static constexpr std::size_t size() noexcept { return kDataImpl.enum_size; }

    static constexpr Enum at(std::size_t i) noexcept {
        return Enum(kDataImpl.vals[i]);
    }

    static constexpr std::string_view nameAt(std::size_t i) noexcept {
        int64_t index = kDataImpl.indexes[i];
        return kDataImpl.names_arr[index];
    }
};

enum EN {
    ONE,
    TWO,
    THREE,
};

enum class Shape {  // : int
    SQUARE = 1,
    CIRCLE = 5,
    LINE,
    POINT = -2
};

// static_assert(EnumeratorTraits<Shape>::nameAt(0) == "POINT");

// check compile time capabilities
static_assert(EnumeratorTraits<Shape>::size() == 4);
// static_assert(EnumeratorTraits<Shape>::size() == 3);
static_assert(EnumeratorTraits<Shape>::nameAt(0) == "POINT");
static_assert(EnumeratorTraits<Shape>::at(0) == Shape::POINT);
static_assert(EnumeratorTraits<Shape>::at(1) == Shape::SQUARE);
static_assert(EnumeratorTraits<Shape>::at(3) == Shape::LINE);

template <typename T>
void Foo() = delete;

// static_assert(EnumeratorTraits<Shape>::nameAt(0) == "POINT");

constexpr auto val = EnumeratorTraits<Shape>::nameAt(0);

int main() {
    std::cout << '<' << val << ">\n";
    // std::cout << (EnumeratorTraits<Shape>::nameAt(0) == "POINT") << '\n';

    // GetEnumValueNameImpl<EN(3)>();
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
