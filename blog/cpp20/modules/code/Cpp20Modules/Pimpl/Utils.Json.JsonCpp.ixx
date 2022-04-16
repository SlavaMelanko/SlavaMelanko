module;

#include <json/json.h>

export module Utils.Json:JsonCpp;

namespace utils::json::impl {

namespace {

Json::Value Parse(const std::string& data)
{
    Json::Value root;
    Json::Reader reader;
    reader.parse(data, root);

    return root;
}

} // namespace

class Document
{
public:
    Document() = default;
    explicit Document(const std::string& data)
        : m_document{ Parse(std::string{data}) }
    {}

    Document(Document&& document) noexcept = default;
    Document& operator=(Document&& document) noexcept = default;

    template<class T>
    auto get(const std::string& key) const
    {
        if constexpr (std::is_same_v<T, bool>) {
            return m_document[key].asBool();
        }
        else if constexpr (std::is_same_v<T, int>) {
            return m_document[key].asInt();
        }
        else if constexpr (std::is_same_v<T, double>) {
            return m_document[key].asDouble();
        }
        else if constexpr (std::is_same_v<T, std::string>) {
            return m_document[key].asString();
        }
    }

    template<typename T>
    void set(const std::string& key, T value) { m_document[key] = value; }

    bool contains(const std::string& key) const { return m_document.isMember(key); }

    bool empty() const noexcept { return m_document.empty(); }

    std::string dump() const { return m_document.toStyledString(); }

private:
    Json::Value m_document;
};

} // namespace utils::json::impl
