#include <range/v3/algorithm.hpp>
#include <range/v3/action.hpp>
#include <range/v3/view.hpp>

int main()
{
  const std::string input = "What is a Bitcoin? ...";

  std::stringstream sin{input};
  auto words = ranges::getlines(sin, ' ')
    | ranges::views::transform([](const auto &word) {  // "Bitcoin?"
       return ranges::views::all(word)                 // ['B','i','t','c','o','i','n','?']
         | ranges::views::trim(std::not_fn(::isalpha)) // ['B','i','t','c','o','i','n']
         | ranges::views::transform(::tolower)         // ['b','i','t','c','o','i','n']
         | ranges::to<std::string>;                    // "bitcoin"
      })
    | ranges::views::filter([](const auto &word) {
        return !word.empty(); }) // because " - " is an empty string after transforming
    | ranges::to_vector;

  std::cout << ranges::views::all(words) << std::endl;
}

