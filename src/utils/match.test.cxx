#include <catch2/catch.hpp>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <iostream>
#include <string>
#include <type_traits>
#include <utils/match.hxx>
#include <variant>

TEST_CASE("match test")
{
    using namespace std::literals;
    using var_t = std::variant<int, float, std::string>;

    auto var7 { var_t { 7 } };
    auto varstr { var_t { "Hello"s } };
    auto varf { var_t { 6.78f } };

    SECTION("match with std::visit")
    {
        std::visit(
            cxl::utils::match {
                [](std::string& s) { fmt::print("s: std::string = {}\n", s); },
                [](int& i) { fmt::print("i: int = {}\n", i); },
                [](float& f) { fmt::print("s: float = {}\n", f); },
                [](cxl::utils::match_any) { fmt::print("Other\n"); }
            },
            var7
        );

        auto r = std::visit(
            cxl::utils::match {
                []([[maybe_unused]] std::string& s) { return "String"s; },
                []([[maybe_unused]] int& i) { return "Int"s; },
                []([[maybe_unused]] float& f) { return "Float"s; },
                [](cxl::utils::match_any) { return "Other"s; } },
            varf
        );

        REQUIRE(r == "Float"s);

        fmt::print("r = {}\n", r);
    }

    SECTION("match expression syntax sugar") 
    {
        auto print_match = cxl::utils::match {
            [](std::string s) { fmt::print("s: std::string = {}\n", s); },
            [](int i) { fmt::print("i: int = {}\n", i); },
            [](float f) { fmt::print("s: float = {}\n", f); },
            [](cxl::utils::match_any) { fmt::print("Other\n"); }
        };

        using namespace cxl;

        auto name_match = cxl::utils::match {
            []([[maybe_unused]] std::string s) { return "String"s; },
            []([[maybe_unused]] int i) { return "Int"s; },
            []([[maybe_unused]] float f) { return "Float"s; },
            [](utils::match_any) { return "Other"s; }
        };

        SECTION("Regular match expression")
        {
            varstr >> cxl::utils::match {
                [](std::string s) { fmt::print("s: std::string = {}\n", s); },
                [](int i) { fmt::print("i: int = {}\n", i); },
                [](float f) { fmt::print("s: float = {}\n", f); },
                [](cxl::utils::match_any) { fmt::print("Other\n"); }
            };

            varf >> print_match;

            REQUIRE(std::is_void_v<decltype(var7 >> name_match)> == true);
        }

        SECTION("Returning match expression")
        {
            auto r = varstr << cxl::utils::match {
                []([[maybe_unused]] std::string s) { return "String"s; },
                []([[maybe_unused]] int i) { return "Int"s; },
                []([[maybe_unused]] float f) { return "Float"s; },
                [](cxl::utils::match_any) { return "Other"s; }
            };

            fmt::print("r = {}\n", r);
            REQUIRE(r == "String");

            auto name = var7 << name_match;
            fmt::print("name = {}\n", name);
            REQUIRE(name == "Int");
        }
    }
}