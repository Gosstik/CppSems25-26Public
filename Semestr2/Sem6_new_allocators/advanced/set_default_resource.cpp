#include <memory_resource>

struct TestResource : public std::pmr::memory_resource {
  public:
    explicit TestResource(
        std::pmr::memory_resource* upstream = std::pmr::get_default_resource())
        : upstream_(upstream) {}

  protected:
    void* do_allocate(size_t bytes, size_t alignment) override {
        return upstream_->allocate(bytes, alignment);
    }

    void do_deallocate(void* p, size_t bytes, size_t alignment) override {
        upstream_->deallocate(p, bytes, alignment);
    }

    bool do_is_equal(
        const std::pmr::memory_resource& other) const noexcept override {
        return upstream_->is_equal(other);
    }

  private:
    std::pmr::memory_resource* upstream_;
};

int main() {
    static TestResource new_default(std::pmr::new_delete_resource());
    std::pmr::set_default_resource(&new_default);
    // ...
}
