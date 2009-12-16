//----------------------------------------------------------------------------
/** @file DfsData.hpp
 */
//----------------------------------------------------------------------------

#ifndef DFSDATA_H
#define DFSDATA_H

#include "Hex.hpp"
#include "ConstBoard.hpp"

_BEGIN_BENZENE_NAMESPACE_

//----------------------------------------------------------------------------

/** A solved state. Stored in a TT or DB. Matches
    TransTableStateConcept.
*/
struct DfsData
{
    /** Marks the proof as that of a transposition of some other
        state. */
    static const int FLAG_TRANSPOSITION = 1;

    /** Marks the proof as a mirror transposition of some other
        state. */
    static const int FLAG_MIRROR_TRANSPOSITION = 2;

    //--------------------------------------------------------------------

    /** True if player to move wins. */
    bool win;

    /** Flags. */
    int flags;
    
    /** Number of states in proof-tree of this result. */
    int numstates;
    
    /** Number of moves losing player can delay until winning
        player has a winning virtual connection. */
    int nummoves;

    /** Best move in this state. 
        Very important in winning states, not so important in losing
        states. That is, in winning states this move *must* be a
        winning move, in losing states this move is "most blocking",
        but the definition is fuzzy. */
    HexPoint bestmove;

    //--------------------------------------------------------------------

    /** Contructs state with default values. */
    DfsData();
    
    /** Initializes state to given values. */
    DfsData(bool w, int nstates, int nmoves, HexPoint bmove);

    /** @name TransTableStateConcept */
    // @{
    
    /** Returns true if this state is not the same as that built by
        the default constructor. */
    bool Initialized() const;

    /** If true, then this will give up its TT slot to other.
        @note ALWAYS RETURNS TRUE FOR NOW!  */
    bool ReplaceWith(const DfsData& other) const;
    
    // @} 

    /** @name PositionDBStateConcept. */
    // @{

    int PackedSize() const;

    byte* Pack() const;

    void Unpack(const byte* t);

    void Rotate(const ConstBoard& brd);

    // @}
};

inline DfsData::DfsData()
    : win(false), 
      flags(0), 
      numstates(0), 
      nummoves(0), 
      bestmove(INVALID_POINT)
{ 
}
    
inline DfsData::DfsData(bool w, int nstates, int nmoves, 
                                HexPoint bmove)
    : win(w),
      flags(0),
      numstates(nstates),
      nummoves(nmoves),
      bestmove(bmove)
{ 
}

inline bool DfsData::Initialized() const
{
    return bestmove != INVALID_POINT;
}

inline bool DfsData::ReplaceWith(const DfsData& other) const
{
    UNUSED(other);
    return true;
}

//----------------------------------------------------------------------------

_END_BENZENE_NAMESPACE_

#endif // DFSDATA_H
