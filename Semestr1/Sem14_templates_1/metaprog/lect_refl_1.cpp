// TODO: add string concept
template <auto name>
struct NameMixin {
  static constexpr auto kName = name;
};

// Legacy from C
#define CLASS(NAME) class NAME : NameMixin< #NAME _cstr>

CLASS(FOO) {
  // ...
};

// Also use in Unreal Engine or QT in codegen