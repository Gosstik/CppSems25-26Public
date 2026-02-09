template <int X, typename C>
class Smth1 {
  C value;

  int GetX() {
    return X;
  }
};

//////////////////////

// Will compile?

template <int X, typename C>
class Smth2 {
  C value;

  int GetXWrapper() {
    return value.member;
  }
};

//////////////////////

// Will compile?

// Hint: dependent names and two phase name lookup
// dependent name --- part of code
// dependent from template parameter
// dependent => resolve after instantiation
// independent => resolve immediately

struct B {};

template <int X, typename C>
class Smth3 {
  B value;

  int getX() {
    return value.member;
  }
};
