#ifndef EXAMREAL_SCORETRACKERCOMPONENT_H
#define EXAMREAL_SCORETRACKERCOMPONENT_H

class ScoreTrackerComponent : public Component{
public:
    int GetScore(){
        return score;
    }

    void SetScore(int newScore){
        score = newScore;
    }

private:
    int score = 0;
};

#endif //EXAMREAL_SCORETRACKERCOMPONENT_H
