#pragma once
#include "Move.h"

class MoveIterator {
public:
    MoveIterator(typename vector<Move>::iterator start) : current(start) {}

    Move& operator*() {
        return *current;
    }

    MoveIterator& operator++() {
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

private:
    std::vector<Move> data;
};
