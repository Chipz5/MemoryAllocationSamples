#include "Vector3.h"
#include "Utilities.h"
#include "Vector4.h"
#include "Timing/Timing.h"
#include<iostream>
#include "Character.cpp"



/*
Time Taken :

Character : 284.3851 ms
FastCharacter : 263.82670 ms
SoACharacter : 261.85810 ms
*/

character item[8192];
fastCharacter fast[8192];
SoACharacterData soa;
double UpdateCharacters(int NumRuns) {
    float no = rand() % 10;
    Engine::Timing::tick start = Engine::Timing::GetCurrentTickCounter();
    item[NumRuns].processVelocity(Engine::Vector4(no, no, no, no));
    return Engine::Timing::GetTimeDiffInMilliseconds(start, Engine::Timing::GetCurrentTickCounter());
}

double UpdateFastCharacters(int NumRuns) {
    float no = rand() % 10;
    Engine::Timing::tick start = Engine::Timing::GetCurrentTickCounter();
    fast[NumRuns].processVelocity(Engine::Vector4(no, no, no, no));
    return Engine::Timing::GetTimeDiffInMilliseconds(start, Engine::Timing::GetCurrentTickCounter());
}


double UpdateSoACharacters(int NumRuns) {
    float no = rand() % 10;
    Engine::Timing::tick start = Engine::Timing::GetCurrentTickCounter();
    soa.hotDatas[NumRuns].processVelocity(Engine::Vector4(no, no, no, no));
    return Engine::Timing::GetTimeDiffInMilliseconds(start, Engine::Timing::GetCurrentTickCounter());
}

int main()
{
using namespace Engine;
// one time init
Engine::Timing::Initialize();
unsigned int NumRuns = 8192;
double UpdateCharactersTime = 0.0;
double UpdateFastCharactersTime = 0.0;
double UpdateSoACharactersTime = 0.0;
for (int i = 0; i < 1000; i++) {
    NumRuns = 8192;
    while (NumRuns--)
    {
        UpdateCharactersTime += UpdateCharacters(NumRuns);
        UpdateFastCharactersTime += UpdateFastCharacters(NumRuns);
        UpdateSoACharactersTime += UpdateSoACharacters(NumRuns);
    }
}
printf("Update Characters time %fms.\n", UpdateCharactersTime);
printf("Update FastCharacters time %fms.\n", UpdateFastCharactersTime);
printf("Update SoACharacters time %fms.\n", UpdateSoACharactersTime);

return 0;
}

