export module Utils.Json;

import :JsonCpp;

import std.core;
import std.threading;

namespace utils::json {

namespace impl {
class Document;
} // namespace impl

export class Document
{
public:
    Document()
        : m_impl{ std::make_unique<impl::Document>() }
    {}
    explicit Document(const std::string &data)
        : m_impl{ std::make_unique<impl::Document>(data) }
    {}

    Document(Document&& document) noexcept = default;
    Document& operator=(Document&& document) noexcept = default;

    ~Document() noexcept = default;

    bool getBool(const std::string &key) const { return m_impl->get<bool>(key); }
    void setBool(const std::string &key, const bool value) { m_impl->set(key, value); }

    int getInt(const std::string &key) const { return m_impl->get<int>(key); }
    void setInt(const std::string &key, const int value) { m_impl->set(key, value); }

    double getDouble(const std::string &key) const { return m_impl->get<double>(key); }
    void setDouble(const std::string &key, const double& value) { m_impl->set(key, value); }

    std::string getString(const std::string &key) const { return m_impl->get<std::string>(key); }
    void setString(const std::string &key, const std::string& value) { m_impl->set(key, value); }

    bool contains(const std::string &key) const { return m_impl->contains(key); }

    bool empty() const noexcept { return !m_impl || m_impl->empty(); }

    std::string dump() const { return m_impl->dump(); }

private:
    std::unique_ptr<impl::Document> m_impl;
};

} // namespace utils::json
