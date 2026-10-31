template <typename... Args> class FormatString {
public:
  const char *str;
  consteval FormatString(const char *string) { str = string; };
};
