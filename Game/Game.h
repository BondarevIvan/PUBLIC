#pragma once
#include <Geometry/Point.h>

#include <memory>

namespace NGame
{
    enum EGameParameters
    {
        EGP_BEADS_COUNT = 12,
        EGP_NECKLACE_SIZE = EGP_BEADS_COUNT,
        EGP_MOD = EGP_BEADS_COUNT,
    };
    enum EDirection
    {
        ED_LEFT = -1,
        ED_RIGHT = 1,
    };
    class Bead
    {
    public:
        Bead() = delete;
        Bead(int i_number);
        Bead(const Bead& i_bead) = default;
        int getNumber() const;
        static NGeometry::Point2 calculatePosition(int i_position, 
                                                   double i_radius = 1.);
    private:
        int c_number;   // 0, 1, 2, 3, ...
    };
    using BeadPtr = std::shared_ptr<Bead>;
    class Necklace
    {
    public:
        Necklace();
        Bead& operator[](int i_id);
        const Bead& operator[](int i_id) const;
    private:
        std::array<BeadPtr, EGP_NECKLACE_SIZE> c_beads;
    };
    using NecklacePtr = std::shared_ptr<Necklace>;
    class Cycle
    {
    public:
        Cycle() = delete;
        Cycle(const Cycle&) = delete;
        Cycle(Necklace& i_necklace, int i_size, int i_begin);
        void rotateLeft();
        void rotateRight();
        int getSize() const;
        int getBegin() const;
        int getStep() const;
        int next(int i_pos) const;
        void shift(int i_dist = 1);
    private:
        Necklace& c_necklace;
        int c_begin;
        int c_step;
    };
    using CyclePtr = Cycle*;
    class Game
    {
    public:
        Game();
        Game(const Game&) = delete;
        void shiftCycleBySize(int i_size, EDirection i_bias);
        void rotateCycleBySize(int i_size, EDirection i_bias);
        void show();
        std::vector<CyclePtr>::const_iterator beginCycle() const;
        std::vector<CyclePtr>::const_iterator endCycle() const;
        Necklace& getNecklace();
    private:
        NecklacePtr c_necklace;
        const std::vector<int> CycleSizes = { 2, 3, 4, 6, 12 };
        std::vector<CyclePtr> c_cycles;
    private:
        void shiftCycle(Cycle& io_cycle, EDirection i_bias);
        void rotateCycle(Cycle& io_cycle, EDirection i_bias);
    };
};