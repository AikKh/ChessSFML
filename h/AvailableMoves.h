#pragma once
#include "Move.h"

class MoveIterator {
public:
    MoveIterator(typename vector<Move>::iterator start) : current(start) {}

    const Move& operator*() const {
        return *current;
    }

    const MoveIterator& operator++() {
        ++current;
        return *this;
    }

    bool operator==(const MoveIterator& other) const {
        return current == other.current;
    }

    bool operator!=(const MoveIterator& other) const {
        return !(*this == other);
    }

private:
	typename vector<Move>::iterator current;
};

// Make more light weight
class AvailableMoves {
public:
    //AvailableMoves(std::initializer_list<Move> elements) : data(elements) {}
    AvailableMoves() = default;

    MoveIterator begin() {
        return MoveIterator(data.begin());
    }

    MoveIterator end() {
        return MoveIterator(data.end());
    }

    void Add(Move move) {
        data.push_back(move);
    }

    AvailableMoves operator+(AvailableMoves&& other)
    {
        for (auto& move : other) {
            Add(move);
        }
        return *this;
    }

    AvailableMoves operator+=(AvailableMoves& other)
    {
        *this = *this + std::move(other);
        return *this;
    }

private:
    std::vector<Move> data;
};
