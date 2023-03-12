#include<iostream>
#include<windows.h>
#include<unistd.h>
using namespace std;

void ClearScreen(){

    cout << "\033[2J\033[1;1H";
    //thank you catzilla from stackoverflow
}

bool TowerSortedCheck(int TowerHeight, int Tower[]){

    bool Result = true;
    int PreviousPosition = 0;

    //checks if last postions number was lower than "i" position
    //starts at 1 as to skip first position which is always 0
    for(int i = 1; i < TowerHeight; i++){

        if(PreviousPosition < Tower[i]){

            PreviousPosition = Tower[i];
        } else{

            Result = false;
            break;
        }        
    }
    return Result;
}

bool TowerEmptyCheck(int TowerHeight, int Tower[]){

    bool Result = true;

    //simply checks if all postions are 0
    for(int i = 0; i < TowerHeight; i++){

        //if a position isnt empty, represented by a zero, returns false
        if(Tower[i] != 0){

            Result = false;
        }
    }
    return Result;
}

int TowerTopDiskSizeCheck(int TowerHeight, int CheckedTower[]){

    int Result = 0;

    for(int i = 1; i < TowerHeight; i++){

        //starting at second tower position, checks if "i" position isnt 0
        //if true, returns this first non zero in tower
        if(CheckedTower[i] != 0){

            Result = CheckedTower[i];
            break;
        }
    
    }
    return Result;
}

int TowerTopDiskPositionCheck(int TowerHeight, int CheckedTower[]){

    //simply returns "i", if "i" position in tower is not zero
    int Result = TowerHeight;

    //starts at 1 as to skip first position in tower, which is always empty
    for(int i = 1; i < TowerHeight; i++){

        if(CheckedTower[i] != 0){

            Result = i;
            break;
        }
        
    }
    return Result;
}

void DiskTransfer(int TowerHeight, int HomeTower[], int DestinationTower[]){

    int TravellingDiskSize = TowerTopDiskSizeCheck(TowerHeight, HomeTower);
    int TravellingDiskPosition = TowerTopDiskPositionCheck(TowerHeight, HomeTower);
    int DestinationTowerDestinationPosition = TowerTopDiskPositionCheck(TowerHeight, DestinationTower) - 1;

    DestinationTower[DestinationTowerDestinationPosition] = TravellingDiskSize;
    HomeTower[TravellingDiskPosition] = 0;

}

void TowersPrinter(int TowerHeight, int FirstTower[], int SecondTower[], int ThirdTower[]){

    //dare i say self explanatory, prints the towers

    for (int i = 0; i < TowerHeight; i++){

    cout << "    " << FirstTower[i] << "    " << SecondTower[i] << "    " << ThirdTower[i] << "\n";

    }
}

//MAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAIN
//MAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAINMAIN

int main(){

    cout << "Enter tower height: ";

    int TowerHeight;

    cin >> TowerHeight;

    //as to keep "Enter tower height" on screen
    //for long enough to read it after input
    sleep(1);

    TowerHeight += 1;

    int FirstTower[TowerHeight];
    int SecondTower[TowerHeight];
    int ThirdTower[TowerHeight];

    ClearScreen();

    //fills the three tower arrays with disks represented by positive  
    //whole numbers, empty space represented by zeroes
    //first position is always 0 for readability
    for (int i = 0; i < TowerHeight; i++){

        FirstTower[i] = i;
        SecondTower[i] = 0;
        ThirdTower[i] = 0;

    }

    bool Success = false;

    bool firstTowerSorted = false;
    bool secondTowerSorted = false;
    bool thirdTowerSorted = false;
    
    bool firstTowerEmpty = false;
    bool secondTowerEmpty = false;
    bool thirdTowerEmpty = false;

    int homeTowerTopDiskSize = 0;
    int targetTowerTopDiskSize = 0;
    int smallestDiskCurrentTower = 1;

    ClearScreen();
    TowersPrinter(TowerHeight, FirstTower, SecondTower, ThirdTower);
    sleep(1);

    //solving loop
    while(Success == false){

        if(Success == false){

            //moves smallest disk
            if(TowerHeight % 2 == 0){

                //even
                if(smallestDiskCurrentTower == 1){

                    DiskTransfer(TowerHeight, FirstTower, SecondTower);
                    smallestDiskCurrentTower = 2;

                } else if (smallestDiskCurrentTower == 2){

                    DiskTransfer(TowerHeight, SecondTower, ThirdTower);
                    smallestDiskCurrentTower = 3;

                } else {

                    DiskTransfer(TowerHeight, ThirdTower, FirstTower);
                    smallestDiskCurrentTower = 1;
                }
                
            } else{

                //odd
                if(smallestDiskCurrentTower == 1){

                    DiskTransfer(TowerHeight, FirstTower, ThirdTower);
                    smallestDiskCurrentTower = 3;

                } else if (smallestDiskCurrentTower == 3){

                    DiskTransfer(TowerHeight, ThirdTower, SecondTower);
                    smallestDiskCurrentTower = 2;

                } else {

                    DiskTransfer(TowerHeight, SecondTower, FirstTower);
                    smallestDiskCurrentTower = 1;
                }
            }
            
            ClearScreen();
            TowersPrinter(TowerHeight, FirstTower, SecondTower, ThirdTower);
            sleep(1);
        }
    
        //checks if puzzle is solved
        firstTowerSorted = TowerEmptyCheck(TowerHeight, FirstTower);
        secondTowerSorted = TowerEmptyCheck(TowerHeight, SecondTower);
        thirdTowerSorted = TowerSortedCheck(TowerHeight, ThirdTower);

        if(firstTowerSorted && secondTowerSorted && thirdTowerSorted){

            Success = true;
        }

        if(Success == false){

            //moves non smallest disk
            if(smallestDiskCurrentTower == 1){

                homeTowerTopDiskSize = TowerTopDiskSizeCheck(TowerHeight, SecondTower);
                targetTowerTopDiskSize = TowerTopDiskSizeCheck(TowerHeight, ThirdTower);

                if(homeTowerTopDiskSize != 0 && targetTowerTopDiskSize > homeTowerTopDiskSize || targetTowerTopDiskSize == 0){

                    DiskTransfer(TowerHeight, SecondTower, ThirdTower);

                } else{

                    homeTowerTopDiskSize = TowerTopDiskSizeCheck(TowerHeight, ThirdTower);
                    targetTowerTopDiskSize = TowerTopDiskSizeCheck(TowerHeight, SecondTower);

                    if(homeTowerTopDiskSize != 0 && targetTowerTopDiskSize > homeTowerTopDiskSize || targetTowerTopDiskSize == 0){

                        DiskTransfer(TowerHeight, ThirdTower, SecondTower);
                    }
                }

            } else if(smallestDiskCurrentTower == 2){

                homeTowerTopDiskSize = TowerTopDiskSizeCheck(TowerHeight, FirstTower);
                targetTowerTopDiskSize = TowerTopDiskSizeCheck(TowerHeight, ThirdTower);

                if(homeTowerTopDiskSize != 0 && targetTowerTopDiskSize > homeTowerTopDiskSize || targetTowerTopDiskSize == 0){

                    DiskTransfer(TowerHeight, FirstTower, ThirdTower);

                } else{

                    homeTowerTopDiskSize = TowerTopDiskSizeCheck(TowerHeight, ThirdTower);
                    targetTowerTopDiskSize = TowerTopDiskSizeCheck(TowerHeight, FirstTower);

                    if(homeTowerTopDiskSize != 0 && targetTowerTopDiskSize > homeTowerTopDiskSize || targetTowerTopDiskSize == 0){

                        DiskTransfer(TowerHeight, ThirdTower, FirstTower);
                    }
                }
                
            } else if(smallestDiskCurrentTower == 3){

                homeTowerTopDiskSize = TowerTopDiskSizeCheck(TowerHeight, FirstTower);
                targetTowerTopDiskSize = TowerTopDiskSizeCheck(TowerHeight, SecondTower);

                if(homeTowerTopDiskSize != 0 && targetTowerTopDiskSize > homeTowerTopDiskSize || targetTowerTopDiskSize == 0){

                    DiskTransfer(TowerHeight, FirstTower, SecondTower);

                } else{

                    homeTowerTopDiskSize = TowerTopDiskSizeCheck(TowerHeight, SecondTower);
                    targetTowerTopDiskSize = TowerTopDiskSizeCheck(TowerHeight, FirstTower);

                    if(homeTowerTopDiskSize != 0 && targetTowerTopDiskSize > homeTowerTopDiskSize || targetTowerTopDiskSize == 0){

                        DiskTransfer(TowerHeight, SecondTower, FirstTower);
                    }
                }
            }
            
            ClearScreen();
            TowersPrinter(TowerHeight, FirstTower, SecondTower, ThirdTower);
            sleep(1);
        }

        //checks if puzzle is solved
        firstTowerSorted = TowerEmptyCheck(TowerHeight, FirstTower);
        secondTowerSorted = TowerEmptyCheck(TowerHeight, SecondTower);
        thirdTowerSorted = TowerSortedCheck(TowerHeight, ThirdTower);

        if(firstTowerSorted && secondTowerSorted && thirdTowerSorted){

            Success = true;
        }
    }
    
    ClearScreen();
    TowersPrinter(TowerHeight, FirstTower, SecondTower, ThirdTower);

    return 0;
}