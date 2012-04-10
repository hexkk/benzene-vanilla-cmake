//----------------------------------------------------------------------------
/** @file VCUtil.cpp */
//----------------------------------------------------------------------------

#include "VCUtil.hpp"
#include "VCS.hpp"
#include "HexBoard.hpp"
#include "BoardUtil.hpp"

using namespace benzene;

//----------------------------------------------------------------------------

bitset_t VCUtil::GetMustplay(const HexBoard& brd, HexColor color)
{
    HexColor other = !color;
    if (brd.Cons(other).FullExists())
        return EMPTY_BITSET;
    else
        return brd.GetPosition().GetEmpty() & brd.Cons(other).SemiIntersection();
}

//----------------------------------------------------------------------------

bool VCUtil::ValidEdgeBridge(const StoneBoard& brd, const bitset_t& carrier, 
                             HexPoint& endpoint, HexPoint& edge)
{
    if (carrier.count() != 2) 
        return false;
    if ((brd.GetOccupied() & carrier).any()) 
        return false;
    std::vector<HexPoint> miai;
    BitsetUtil::BitsetToVector(carrier, miai);
    if (!brd.Const().Adjacent(miai[0], miai[1])) 
        return false;
    // Find the two cells adjacent to both
    std::vector<HexPoint> adj;
    for (BoardIterator n1(brd.Const().Nbs(miai[0])); n1; ++n1)
        for (BoardIterator n2(brd.Const().Nbs(miai[1])); n2; ++n2)
            if (*n1 == *n2) 
                adj.push_back(*n1);
    BenzeneAssert(adj.size() == 2);
    // Pick the edge and endpoint
    for (std::size_t i = 0; i < 2; ++i) 
    {
        if (HexPointUtil::isEdge(adj[i])) 
        {
            edge = adj[i];
            endpoint = adj[i^1];
            return true;
        }
    }
    // Did not touch an edge, so return false
    return false;
}

//----------------------------------------------------------------------------
