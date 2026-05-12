#include <memory>

// TODO: why do we need that ???

struct Node {
    std::shared_ptr<Node> GetShared() { return std::shared_ptr<Node>(this); }
};

int main() {
    std::shared_ptr<Node> bp1 = std::make_shared<Node>();
    std::shared_ptr<Node> bp2 = bp1->GetShared();
}
