#include "Game.h"

#include <iostream>
#include <assert.h>

namespace NGame
{
    namespace NModMath
    {
        int sum(int i_first, int i_second)
        {
            return (i_first + i_second + (EGP_MOD << 2)) % EGP_MOD;
        }
        int difference(int i_minuend, int i_subtrahend)
        {
            return (i_minuend - i_subtrahend + (EGP_MOD << 2)) % EGP_MOD;
        }
        int getClass(int i_number)
        {
            return i_number % EGP_MOD;
        }
    }
    Bead::Bead(int i_number) :
        c_number(i_number)
    {
    }
    int Bead::getNumber() const
    {
        return c_number;
    }
    
    NGeometry::Point2 Bead::calculatePosition(int i_position,
                                              double i_radius)
    {
        double angle = 2 * M_PI / EGP_BEADS_COUNT;
        return NGeometry::Point2(std::vector<double>{
                cos(angle * i_position) * i_radius,
                sin(angle * i_position) * i_radius });
    }

    Necklace::Necklace()
    {
        for (int i = 0; i < EGP_NECKLACE_SIZE; ++i)
            c_beads[i] = std::make_shared<Bead>(Bead(i));
    }
    Bead& Necklace::operator[](int i_id)
    {
        return *c_beads[NModMath::getClass(i_id)];
    }
    const Bead& Necklace::operator[](int i_id) const
    {
        return *c_beads[NModMath::getClass(i_id)];
    }


    Cycle::Cycle(Necklace& i_necklace, int i_size, int i_begin) :
        c_necklace(i_necklace),
        c_begin(NModMath::getClass(i_begin))
    {
        assert(i_size != 0);
        assert(EGP_MOD % i_size == 0);
        c_step = EGP_MOD / i_size;
    }
    int Cycle::getSize() const
    {
        return EGP_MOD / c_step;
    }
    int Cycle::getBegin() const
    {
        return c_begin;
    }
    int Cycle::getStep() const
    {
        return c_step;
    }
    int Cycle::next(int i_pos) const
    {
        return NModMath::sum(i_pos, c_step);
    }

    void Cycle::shift(int i_dist)
    {
        c_begin = NModMath::sum(c_begin, i_dist);
    }


    template<class T>
    void rotateVectorRight(std::vector<std::pair<int, T>>& io_order)
    {
        if (io_order.empty())
            return;
        auto last = io_order.back().first;
        for (int i = io_order.size() - 1; i >= 1; --i)
            io_order[i].first = io_order[i - 1].first;
        io_order[0].first = last;
    }
    template<class T>
    void rotateVectorLeft(std::vector<std::pair<int, T>>& io_order)
    {
        if (io_order.empty())
            return;
        auto first = io_order[0].first;
        for (int i = 0; (i + 1) < io_order.size(); ++i)
            io_order[i].first = io_order[i + 1].first;
        io_order.back().first = first;        
    }
    void Cycle::rotateLeft()
    {
        std::vector<std::pair<int, Bead>> order;
        for (int pos = c_begin, cnt = EGP_MOD / c_step; cnt;
                 pos = NModMath::sum(pos, c_step), --cnt)
        {
            order.push_back({ pos, c_necklace[pos] });
        }
        rotateVectorLeft(order);
        for (auto [id, bead] : order)
        {
            c_necklace[id] = bead;
        }
    }
    void Cycle::rotateRight()
    {
        std::vector<std::pair<int, Bead>> order;
        for (int pos = c_begin, cnt = EGP_MOD / c_step; cnt;
                 pos = NModMath::sum(pos, c_step), --cnt)
        {
            order.push_back({ pos, c_necklace[pos] });
        }
        rotateVectorRight(order);
        for (auto [id, bead] : order)
            c_necklace[id] = bead;
    }

    Game::Game() :
        c_necklace(std::make_shared<Necklace>(Necklace{}))
    {
        for (auto size : CycleSizes)
            c_cycles.push_back(new Cycle(*c_necklace, size, 0));
    }
    void Game::shiftCycle(Cycle& io_cycle, EDirection i_bias)
    {
        io_cycle.shift(i_bias);
    }
    void Game::shiftCycleBySize(int i_size, EDirection i_bias)
    {
        for (auto& cycle : c_cycles)
            if (cycle->getSize() == i_size)
            {
                shiftCycle(*cycle, i_bias);
                break;
            }
    }
    void Game::rotateCycleBySize(int i_size, EDirection i_bias)
    {
        for (auto& cycle : c_cycles)
            if (cycle->getSize() == i_size)
            {
                rotateCycle(*cycle, i_bias);
                break;
            }
    }

    void Game::rotateCycle(Cycle& io_cycle, EDirection i_bias)
    {
        if (i_bias == EDirection::ED_LEFT)
            io_cycle.rotateLeft();
        if (i_bias == EDirection::ED_RIGHT)
            io_cycle.rotateRight();
    }
    void Game::show()
    {
        for (int id = 0; id < EGP_NECKLACE_SIZE; ++id)
            std::cout << (*c_necklace)[id].getNumber() << ' ';
        std::cout << std::endl;
    }
    Necklace& Game::getNecklace()
    {
        return *c_necklace;
    }
    std::vector<CyclePtr>::const_iterator Game::beginCycle() const
    {
        return c_cycles.cbegin();
    }
    std::vector<CyclePtr>::const_iterator Game::endCycle() const
    {
        return c_cycles.cend();
    }

}