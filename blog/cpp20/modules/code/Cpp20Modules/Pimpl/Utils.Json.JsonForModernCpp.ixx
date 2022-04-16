module;

#include <nlohmann/json.hpp>

export module Utils.Json:JsonForModernCpp;

namespace utils::json::impl {

class Document
{
public:
    Document() = default;
    explicit Document(const std::string& data)
        : m_document{ nlohmann::json::parse(std::string{data}) }
    {}
    ~Document() noexcept = default;

    Document(Document&& document) noexcept = default;
    Document& operator=(Document&& document) noexcept = default;

    template<class T>
    auto get(const std::string& key) const { return m_document[key].get<T>(); }

    template<typename T>
    void set(const std::string& key, T value) { m_document[key] = value; }

    bool contains(const std::string& key) const { return m_document.contains(key); }

    bool empty() const noexcept { return m_document.empty(); }

    std::string dump() const { return m_document.dump(); }

private:
    nlohmann::json m_document;
};

} // namespace utils::json::impl
