#ifndef POFFENSE1_PLAY_HPP
#define POFFENSE1_PLAY_HPP

#include <utility>
#include "play.hpp"
#include "beliefState.h"
#include "tactic.h"
#include "config.h"

namespace Strategy
{
  class POffense1Play : public Play
  {
    public: 
    inline POffense1Play(const BeliefState& state) : Play(state)
    {
      name = "Offense1";
      assert(HomeTeam::SIZE ==5);
      
      PositionPlay = PLAYTYPE_NO;
      AttackPlay   = PLAYTYPE_YES;
      Tactic::Param param;
      Tactic::Param pAttack;
      pAttack.AttackP.rotateOnError = true;
      
      /* Role 1 - Goalie */
      roleList[0].push_back(std::make_pair(Tactic::GoalieOur,param));
      
      /* Role 2 - Striker */
			param.AttackP.rotateOnError = true;
      roleList[1].push_back(std::make_pair(Tactic::Attack,pAttack));
      
      /* Role 3 - Defender */
      roleList[2].push_back(std::make_pair(Tactic::CoverGoal,param));
      
      /* Role 4 - Mid Field Player/Charger */
      param.BlockP.dist = 1000;
      if(state.pr_ball_in_opp_dbox)
        roleList[3].push_back(std::make_pair(Tactic::ChargeBall,param));
      else
        roleList[3].push_back(std::make_pair(Tactic::Block,param));
      
      /* Role 5 - Support Player */
      roleList[4].push_back(std::make_pair(Tactic::Backup,param));
        
      computeMaxTacticTransits();
    }
    
    inline ~POffense1Play()
    {
      
    }
    
    inline bool applicable(void) const
    {
      if(!state.pr_gameRunning)
        return false;
				
			/*int diff = state.oppGoalCount - state.ourGoalCount;
      if(diff <= 3 &&  ( state.pr_ballOppSide || (!state.pr_nOpponentsOurSide(1) && state.pr_ballOurSide) ) )
        return true;*/
				
      if(state.pr_ballOppSide)
        return true;
      return false;
    }
    
    inline Result done(void) const
    {
      if(state.pr_ballOurSide ) return FAILURE_LOW;
      if(state.pr_oppGoalScored) return FAILURE_HIGH;
      if(state.pr_ballOurSide && state.pr_oppBall) return FAILURE_MED;
      if(state.pr_ourGoalScored) return SUCCESS_HIGH;
      if(state.pr_ball_in_opp_dbox) return SUCCESS_MED;
      return NOT_TERMINATED;
    }
  };
}
#endif // POFFENSE1_PLAY_HPP