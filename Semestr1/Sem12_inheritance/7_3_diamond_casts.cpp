#include <iostream>

struct Granny {};
struct Mom : Granny {};
struct Dad : Granny {};
struct Son : Mom, Dad {};

struct Son1: Mom, Dad {};
struct Son2: Dad, Mom {};

// Up the inheritance hierarchy
void SonToGranny() {
    Son s;
    Granny& g1 = static_cast<Granny&>(s); // CE
    Granny& g2 = static_cast<Mom::Granny&>(s); // !!! CE

    Mom& m = s;
    Granny& mg = m; // OK
}

void SideCast() {
    Son1 s;
    Mom& m = s;
    Dad& d = static_cast<Dad&>(m); // CE
}

// Downcast (cast down the inheritance hierarchy)
void GrannyToSon() {
    Granny g;
    Son& s1 = static_cast<Son&>(g); // CE

    Mom& m = static_cast<Mom&>(g); // OK (possibly UB)
    Son& s2 = static_cast<Son&>(m); // OK (possibly UB)
}

int main() {
    SonToGranny();
    SideCast();
    GrannyToSon();
}
