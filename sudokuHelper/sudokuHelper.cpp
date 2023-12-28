#include <iostream>
#include <tuple>
#include <vector>

using namespace std;



void puzzleStringToMatrix(char *puzzleString, int puzzle[9][9]);
void candidatesStringToMatrix(char *candidatesString, int candidates[9][9][9]);
void puzzleMatrixToString(int puzzle[9][9], char puzzleString[81]);
void candidatesMatrixToString(int candidates[9][9][9], char candidatesString[729]);

bool comparePuzzles(int puzzle1[9][9], int puzzle2[9][9]);
void copyPuzzle(int puzzleSource[9][9], int puzzleDestination[9][9]);

bool checkUserSolution(int userSolution[9][9], int puzzleSolution[9][9]);

void printPuzzle(int puzzle[9][9]);
void printCandidates(int candidates[9][9][9]);

void printValueMethodHuman(string name, tuple<int, int> coordinates, int value);
void printCandidatesMethodHuman(string name, vector<tuple<tuple<int, int>, int>> candidatesToStay, vector<tuple<tuple<int, int>, int>> candidatesToRemove);
void printValueMethodProgram(string name, tuple<int, int> coordinates, int value);
void printCandidatesMethodProgram(string name, vector<tuple<tuple<int, int>, int>> candidatesToStay, vector<tuple<tuple<int, int>, int>> candidatesToRemove);

int characterToInteger(char character);
char integerToCharacter(int integer);

void getPuzzleRow(int puzzle[9][9], int rowIndex, int row[9]);
void getPuzzleColumn(int puzzle[9][9], int columnIndex, int column[9]);
void getPuzzleBox(int puzzle[9][9], int rowIndex, int columnIndex, int box[3][3]);
void getCandidatesRow(int candidates[9][9][9], int rowIndex, int row[9][9]);
void getCandidatesColumn(int candidates[9][9][9], int columnIndex, int column[9][9]);
void getCandidatesBox(int candidates[9][9][9], int rowIndex, int columnIndex, int box[3][3][9]);

bool checkForUniqueSolution(int puzzle[9][9]);

bool solveSudoku(int puzzle[9][9], int rowIndex, int columnIndex, bool avoidSolution, int solutionToAvoid[9][9]);
bool isSafe(int puzzle[9][9], int rowIndex, int columnIndex, int number);

void calculatePossibleCandidates(int puzzle[9][9], int candidates[9][9][9]);

tuple<bool, tuple<int, int>, int> onlyCandidate(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, tuple<int, int>, int> lastPossiblePlaceInRow(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, tuple<int, int>, int> lastPossiblePlaceInColumn(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, tuple<int, int>, int> lastPossiblePlaceInBox(int puzzle[9][9], int candidates[9][9][9]);

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedPairsInRow(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedPairsInColumn(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedPairsInBox(int puzzle[9][9], int candidates[9][9][9]);

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedTriplesInRow(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedTriplesInColumn(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedTriplesInBox(int puzzle[9][9], int candidates[9][9][9]);

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedQuadsInRow(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedQuadsInColumn(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedQuadsInBox(int puzzle[9][9], int candidates[9][9][9]);

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenPairsInRow(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenPairsInColumn(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenPairsInBox(int puzzle[9][9], int candidates[9][9][9]);

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenTriplesInRow(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenTriplesInColumn(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenTriplesInBox(int puzzle[9][9], int candidates[9][9][9]);

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenQuadsInRow(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenQuadsInColumn(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenQuadsInBox(int puzzle[9][9], int candidates[9][9][9]);

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> boxRowReduction(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> boxColumnReduction(int puzzle[9][9], int candidates[9][9][9]);

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> rowBoxReduction(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> columnBoxReduction(int puzzle[9][9], int candidates[9][9][9]);

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> xWingRow(int puzzle[9][9], int candidates[9][9][9]);
tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> xWingColumn(int puzzle[9][9], int candidates[9][9][9]);



int main(int argc, char** argv) {
    int method;
    char *puzzleString = NULL;
    char *userPuzzleString = NULL;
    char *solvedPuzzleString = NULL;

    method = characterToInteger(argv[1][0]);

    puzzleString = argv[2];

    if(method == 2) {
        userPuzzleString = argv[3];
        solvedPuzzleString = argv[4];
    }

    switch(method) {
        case 1: {
            int puzzle[9][9];
            fill_n(&puzzle[0][0], sizeof(puzzle) / sizeof(**puzzle), 0);

            puzzleStringToMatrix(puzzleString, puzzle);

            int workingPuzzle[9][9];
            fill_n(&workingPuzzle[0][0], sizeof(workingPuzzle) / sizeof(**workingPuzzle), 0);

            copyPuzzle(puzzle, workingPuzzle);

            if(checkForUniqueSolution(workingPuzzle) == false) {
                cout << "Sudoku solution not unique" << endl;
                return -1;
            }

            int puzzleSolution[9][9];
            fill_n(&puzzleSolution[0][0], sizeof(puzzleSolution) / sizeof(**puzzleSolution), 0);

            copyPuzzle(puzzle, puzzleSolution);
            
            solveSudoku(puzzleSolution, 0, 0, false, NULL);

            copyPuzzle(puzzle, workingPuzzle);

            int candidates[9][9][9];
            fill_n(&candidates[0][0][0], sizeof(candidates) / sizeof(***candidates), 1);

            calculatePossibleCandidates(workingPuzzle, candidates);

            int difficulty = 1;

            bool solvedStep = false;
            
            do {
                solvedStep = false;

                calculatePossibleCandidates(workingPuzzle, candidates);

                tuple<bool, tuple<int, int>, int> onlyCandidateSolution;

                onlyCandidateSolution = onlyCandidate(workingPuzzle, candidates);

                if(get<0>(onlyCandidateSolution) == true) {
                    solvedStep = true;

                    workingPuzzle[get<0>(get<1>(onlyCandidateSolution))][get<1>(get<1>(onlyCandidateSolution))] = get<2>(onlyCandidateSolution);
                }
                else {
                    tuple<bool, tuple<int, int>, int> lastPossiblePlaceInRowSolution;

                    lastPossiblePlaceInRowSolution = lastPossiblePlaceInRow(workingPuzzle, candidates);

                    if(get<0>(lastPossiblePlaceInRowSolution) == true) {
                        solvedStep = true;

                        workingPuzzle[get<0>(get<1>(lastPossiblePlaceInRowSolution))][get<1>(get<1>(lastPossiblePlaceInRowSolution))] = get<2>(lastPossiblePlaceInRowSolution);
                    }
                    else {
                        tuple<bool, tuple<int, int>, int> lastPossiblePlaceInColumnSolution;

                        lastPossiblePlaceInColumnSolution = lastPossiblePlaceInColumn(workingPuzzle, candidates);

                        if(get<0>(lastPossiblePlaceInColumnSolution) == true) {
                            solvedStep = true;

                            workingPuzzle[get<0>(get<1>(lastPossiblePlaceInColumnSolution))][get<1>(get<1>(lastPossiblePlaceInColumnSolution))] = get<2>(lastPossiblePlaceInColumnSolution);
                        }
                        else {
                            tuple<bool, tuple<int, int>, int> lastPossiblePlaceInBoxSolution;

                            lastPossiblePlaceInBoxSolution = lastPossiblePlaceInBox(workingPuzzle, candidates);

                            if(get<0>(lastPossiblePlaceInBoxSolution) == true) {
                                solvedStep = true;

                                workingPuzzle[get<0>(get<1>(lastPossiblePlaceInBoxSolution))][get<1>(get<1>(lastPossiblePlaceInBoxSolution))] = get<2>(lastPossiblePlaceInBoxSolution);
                            }
                            else {
                                tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedPairsInRowSolution;

                                nakedPairsInRowSolution = nakedPairsInRow(workingPuzzle, candidates);

                                if(get<0>(nakedPairsInRowSolution) == true) {
                                    if(difficulty < 2) {
                                        difficulty = 2;
                                    }

                                    solvedStep = true;

                                    vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                    candidatesToStay = get<1>(nakedPairsInRowSolution);
                                    candidatesToRemove = get<2>(nakedPairsInRowSolution);

                                    for(int index = 0; index < candidatesToRemove.size(); index++) {
                                        candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                    }
                                }
                                else {
                                    tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedPairsInColumnSolution;

                                    nakedPairsInColumnSolution = nakedPairsInColumn(workingPuzzle, candidates);

                                    if(get<0>(nakedPairsInColumnSolution) == true) {
                                        if(difficulty < 2) {
                                            difficulty = 2;
                                        }

                                        solvedStep = true;

                                        vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                        vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                        candidatesToStay = get<1>(nakedPairsInColumnSolution);
                                        candidatesToRemove = get<2>(nakedPairsInColumnSolution);

                                        for(int index = 0; index < candidatesToRemove.size(); index++) {
                                            candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                        }
                                    }
                                    else {
                                        tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedPairsInBoxSolution;

                                        nakedPairsInBoxSolution = nakedPairsInBox(workingPuzzle, candidates);

                                        if(get<0>(nakedPairsInBoxSolution) == true) {
                                            if(difficulty < 2) {
                                                difficulty = 2;
                                            }

                                            solvedStep = true;

                                            vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                            vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                            candidatesToStay = get<1>(nakedPairsInBoxSolution);
                                            candidatesToRemove = get<2>(nakedPairsInBoxSolution);

                                            for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                            }
                                        }
                                        else {
                                            tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedTriplesInRowSolution;

                                            nakedTriplesInRowSolution = nakedTriplesInRow(workingPuzzle, candidates);

                                            if(get<0>(nakedTriplesInRowSolution) == true) {
                                                if(difficulty < 2) {
                                                    difficulty = 2;
                                                }

                                                solvedStep = true;

                                                vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                candidatesToStay = get<1>(nakedTriplesInRowSolution);
                                                candidatesToRemove = get<2>(nakedTriplesInRowSolution);

                                                for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                    candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                }
                                            }
                                            else {
                                                tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedTriplesInColumnSolution;

                                                nakedTriplesInColumnSolution = nakedTriplesInColumn(workingPuzzle, candidates);

                                                if(get<0>(nakedTriplesInColumnSolution) == true) {
                                                    if(difficulty < 2) {
                                                        difficulty = 2;
                                                    }

                                                    solvedStep = true;

                                                    vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                    candidatesToStay = get<1>(nakedTriplesInColumnSolution);
                                                    candidatesToRemove = get<2>(nakedTriplesInColumnSolution);

                                                    for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                        candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                    }
                                                }
                                                else {
                                                    tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedTriplesInBoxSolution;

                                                    nakedTriplesInBoxSolution = nakedTriplesInBox(workingPuzzle, candidates);

                                                    if(get<0>(nakedTriplesInBoxSolution) == true) {
                                                        if(difficulty < 2) {
                                                            difficulty = 2;
                                                        }

                                                        solvedStep = true;

                                                        vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                        vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                        candidatesToStay = get<1>(nakedTriplesInBoxSolution);
                                                        candidatesToRemove = get<2>(nakedTriplesInBoxSolution);

                                                        for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                            candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                        }
                                                    }    
                                                    else {
                                                        tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedQuadsInRowSolution;

                                                        nakedQuadsInRowSolution = nakedQuadsInRow(workingPuzzle, candidates);

                                                        if(get<0>(nakedQuadsInRowSolution) == true) {
                                                            if(difficulty < 2) {
                                                                difficulty = 2;
                                                            }

                                                            solvedStep = true;

                                                            vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                            vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                            candidatesToStay = get<1>(nakedQuadsInRowSolution);
                                                            candidatesToRemove = get<2>(nakedQuadsInRowSolution);

                                                            for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                            }
                                                        }
                                                        else {
                                                            tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedQuadsInColumnSolution;

                                                            nakedQuadsInColumnSolution = nakedQuadsInColumn(workingPuzzle, candidates);

                                                            if(get<0>(nakedQuadsInColumnSolution) == true) {
                                                                if(difficulty < 2) {
                                                                    difficulty = 2;
                                                                }

                                                                solvedStep = true;

                                                                vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                candidatesToStay = get<1>(nakedQuadsInColumnSolution);
                                                                candidatesToRemove = get<2>(nakedQuadsInColumnSolution);

                                                                for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                    candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                }
                                                            }
                                                            else {
                                                                tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedQuadsInBoxSolution;

                                                                nakedQuadsInBoxSolution = nakedQuadsInBox(workingPuzzle, candidates);

                                                                if(get<0>(nakedQuadsInBoxSolution) == true) {
                                                                    if(difficulty < 2) {
                                                                        difficulty = 2;
                                                                    }

                                                                    solvedStep = true;

                                                                    vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                    candidatesToStay = get<1>(nakedQuadsInBoxSolution);
                                                                    candidatesToRemove = get<2>(nakedQuadsInBoxSolution);

                                                                    for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                        candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                    }
                                                                }
                                                                else {
                                                                    tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenPairsInRowSolution;

                                                                    hiddenPairsInRowSolution = hiddenPairsInRow(workingPuzzle, candidates);

                                                                    if(get<0>(hiddenPairsInRowSolution) == true) {
                                                                        if(difficulty < 2) {
                                                                            difficulty = 2;
                                                                        }

                                                                        solvedStep = true;

                                                                        vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                        vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                        candidatesToStay = get<1>(hiddenPairsInRowSolution);
                                                                        candidatesToRemove = get<2>(hiddenPairsInRowSolution);

                                                                        for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                            candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                        }
                                                                    }
                                                                    else {
                                                                        tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenPairsInColumnSolution;

                                                                        hiddenPairsInColumnSolution = hiddenPairsInColumn(workingPuzzle, candidates);

                                                                        if(get<0>(hiddenPairsInColumnSolution) == true) {
                                                                            if(difficulty < 2) {
                                                                                difficulty = 2;
                                                                            }

                                                                            solvedStep = true;

                                                                            vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                            vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                            candidatesToStay = get<1>(hiddenPairsInColumnSolution);
                                                                            candidatesToRemove = get<2>(hiddenPairsInColumnSolution);

                                                                            for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                            }
                                                                        }
                                                                        else {
                                                                            tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenPairsInBoxSolution;

                                                                            hiddenPairsInBoxSolution = hiddenPairsInBox(workingPuzzle, candidates);

                                                                            if(get<0>(hiddenPairsInBoxSolution) == true) {
                                                                                if(difficulty < 2) {
                                                                                    difficulty = 2;
                                                                                }

                                                                                solvedStep = true;

                                                                                vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                candidatesToStay = get<1>(hiddenPairsInBoxSolution);
                                                                                candidatesToRemove = get<2>(hiddenPairsInBoxSolution);

                                                                                for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                    candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                }
                                                                            }
                                                                            else {
                                                                                tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenTriplesInRowSolution;

                                                                                hiddenTriplesInRowSolution = hiddenTriplesInRow(workingPuzzle, candidates);

                                                                                if(get<0>(hiddenTriplesInRowSolution) == true) {
                                                                                    if(difficulty < 2) {
                                                                                        difficulty = 2;
                                                                                    }

                                                                                    solvedStep = true;

                                                                                    vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                    candidatesToStay = get<1>(hiddenTriplesInRowSolution);
                                                                                    candidatesToRemove = get<2>(hiddenTriplesInRowSolution);

                                                                                    for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                        candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                    }
                                                                                }
                                                                                else {
                                                                                    tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenTriplesInColumnSolution;

                                                                                    hiddenTriplesInColumnSolution = hiddenTriplesInColumn(workingPuzzle, candidates);

                                                                                    if(get<0>(hiddenTriplesInColumnSolution) == true) {
                                                                                        if(difficulty < 2) {
                                                                                            difficulty = 2;
                                                                                        }

                                                                                        solvedStep = true;

                                                                                        vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                        vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                        candidatesToStay = get<1>(hiddenTriplesInColumnSolution);
                                                                                        candidatesToRemove = get<2>(hiddenTriplesInColumnSolution);

                                                                                        for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                            candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                        }
                                                                                    }
                                                                                    else {
                                                                                        tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenTriplesInBoxSolution;

                                                                                        hiddenTriplesInBoxSolution = hiddenTriplesInBox(workingPuzzle, candidates);

                                                                                        if(get<0>(hiddenTriplesInBoxSolution) == true) {
                                                                                            if(difficulty < 2) {
                                                                                                difficulty = 2;
                                                                                            }

                                                                                            solvedStep = true;

                                                                                            vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                            vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                            candidatesToStay = get<1>(hiddenTriplesInBoxSolution);
                                                                                            candidatesToRemove = get<2>(hiddenTriplesInBoxSolution);

                                                                                            for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                            }
                                                                                        }
                                                                                        else {
                                                                                            tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenQuadsInRowSolution;

                                                                                            hiddenQuadsInRowSolution = hiddenQuadsInRow(workingPuzzle, candidates);

                                                                                            if(get<0>(hiddenQuadsInRowSolution) == true) {
                                                                                                if(difficulty < 2) {
                                                                                                    difficulty = 2;
                                                                                                }

                                                                                                solvedStep = true;

                                                                                                vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                candidatesToStay = get<1>(hiddenQuadsInRowSolution);
                                                                                                candidatesToRemove = get<2>(hiddenQuadsInRowSolution);

                                                                                                for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                    candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                }
                                                                                            }
                                                                                            else {
                                                                                                tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenQuadsInColumnSolution;

                                                                                                hiddenQuadsInColumnSolution = hiddenQuadsInColumn(workingPuzzle, candidates);

                                                                                                if(get<0>(hiddenQuadsInColumnSolution) == true) {
                                                                                                    if(difficulty < 2) {
                                                                                                        difficulty = 2;
                                                                                                    }

                                                                                                    solvedStep = true;

                                                                                                    vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                    candidatesToStay = get<1>(hiddenQuadsInColumnSolution);
                                                                                                    candidatesToRemove = get<2>(hiddenQuadsInColumnSolution);

                                                                                                    for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                        candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                    }
                                                                                                }
                                                                                                else {
                                                                                                    tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenQuadsInBoxSolution;

                                                                                                    hiddenQuadsInBoxSolution = hiddenQuadsInBox(workingPuzzle, candidates);

                                                                                                    if(get<0>(hiddenQuadsInBoxSolution) == true) {
                                                                                                        if(difficulty < 2) {
                                                                                                            difficulty = 2;
                                                                                                        }

                                                                                                        solvedStep = true;

                                                                                                        vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                        vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                        candidatesToStay = get<1>(hiddenQuadsInBoxSolution);
                                                                                                        candidatesToRemove = get<2>(hiddenQuadsInBoxSolution);

                                                                                                        for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                            candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                        }
                                                                                                    }
                                                                                                    else {
                                                                                                        tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> boxRowReductionSolution;

                                                                                                        boxRowReductionSolution = boxRowReduction(workingPuzzle, candidates);

                                                                                                        if(get<0>(boxRowReductionSolution) == true) {
                                                                                                            if(difficulty < 3) {
                                                                                                                difficulty = 3;
                                                                                                            }

                                                                                                            solvedStep = true;

                                                                                                            vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                            vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                            candidatesToStay = get<1>(boxRowReductionSolution);
                                                                                                            candidatesToRemove = get<2>(boxRowReductionSolution);

                                                                                                            for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                                candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                            }
                                                                                                        }
                                                                                                        else {
                                                                                                            tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> boxColumnReductionSolution;

                                                                                                            boxColumnReductionSolution = boxColumnReduction(workingPuzzle, candidates);

                                                                                                            if(get<0>(boxColumnReductionSolution) == true) {
                                                                                                                if(difficulty < 3) {
                                                                                                                    difficulty = 3;
                                                                                                                }

                                                                                                                solvedStep = true;

                                                                                                                vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                                vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                                candidatesToStay = get<1>(boxColumnReductionSolution);
                                                                                                                candidatesToRemove = get<2>(boxColumnReductionSolution);

                                                                                                                for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                                    candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                                }
                                                                                                            }
                                                                                                            else {
                                                                                                                tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> rowBoxReductionSolution;

                                                                                                                rowBoxReductionSolution = rowBoxReduction(workingPuzzle, candidates);

                                                                                                                if(get<0>(rowBoxReductionSolution) == true) {
                                                                                                                    if(difficulty < 3) {
                                                                                                                        difficulty = 3;
                                                                                                                    }

                                                                                                                    solvedStep = true;

                                                                                                                    vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                                    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                                    candidatesToStay = get<1>(rowBoxReductionSolution);
                                                                                                                    candidatesToRemove = get<2>(rowBoxReductionSolution);

                                                                                                                    for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                                        candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                                    }                                                                                                             
                                                                                                                }
                                                                                                                else {
                                                                                                                    tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> columnBoxReductionSolution;

                                                                                                                    columnBoxReductionSolution = columnBoxReduction(workingPuzzle, candidates);

                                                                                                                    if(get<0>(columnBoxReductionSolution) == true) {
                                                                                                                        if(difficulty < 3) {
                                                                                                                            difficulty = 3;
                                                                                                                        }

                                                                                                                        solvedStep = true;

                                                                                                                        vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                                        vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                                        candidatesToStay = get<1>(columnBoxReductionSolution);
                                                                                                                        candidatesToRemove = get<2>(columnBoxReductionSolution);

                                                                                                                        for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                                            candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                                        }                                                                                                                                                                                                                              
                                                                                                                    }
                                                                                                                    else {
                                                                                                                        tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> xWingRowSolution;

                                                                                                                        xWingRowSolution = xWingRow(workingPuzzle, candidates);

                                                                                                                        if(get<0>(xWingRowSolution) == true) {
                                                                                                                            if(difficulty < 4) {
                                                                                                                                difficulty = 4;
                                                                                                                            }

                                                                                                                            solvedStep = true;

                                                                                                                            vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                                            vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                                            candidatesToStay = get<1>(xWingRowSolution);
                                                                                                                            candidatesToRemove = get<2>(xWingRowSolution);

                                                                                                                            for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                                                candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                                            }
                                                                                                                        }
                                                                                                                        else {
                                                                                                                            tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> xWingColumnSolution;

                                                                                                                            xWingColumnSolution = xWingColumn(workingPuzzle, candidates);

                                                                                                                            if(get<0>(xWingColumnSolution) == true) {
                                                                                                                                if(difficulty < 4) {
                                                                                                                                    difficulty = 4;
                                                                                                                                }

                                                                                                                                solvedStep = true;

                                                                                                                                vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                                                vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                                                candidatesToStay = get<1>(xWingColumnSolution);
                                                                                                                                candidatesToRemove = get<2>(xWingColumnSolution);

                                                                                                                                for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                                                    candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                                                }
                                                                                                                            }
                                                                                                                            else {
                                                                                                                                // new strategy
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                } 
            }while(solvedStep == true);

            bool puzzleSolved;

            puzzleSolved = comparePuzzles(puzzleSolution, workingPuzzle);

            if(puzzleSolved == false) {
                cout << "Solver could not solve puzzle";
                return -1;
            }

            char solverSolvedPuzzleString[81];

            puzzleMatrixToString(workingPuzzle, solverSolvedPuzzleString);

            cout << difficulty << "&";

            for(int index = 0; index < 81; index++) {
                cout << solverSolvedPuzzleString[index];
            }

            break;
        }

        case 2: {
            int puzzle[9][9];
            fill_n(&puzzle[0][0], sizeof(puzzle) / sizeof(**puzzle), 0);

            int userPuzzle[9][9];
            fill_n(&userPuzzle[0][0], sizeof(userPuzzle) / sizeof(**userPuzzle), 0);

            int solvedPuzzle[9][9];
            fill_n(&solvedPuzzle[0][0], sizeof(solvedPuzzle) / sizeof(**solvedPuzzle), 0);

            puzzleStringToMatrix(puzzleString, puzzle);
            puzzleStringToMatrix(userPuzzleString, userPuzzle);
            puzzleStringToMatrix(solvedPuzzleString, solvedPuzzle);

            bool userSolution;

            userSolution = checkUserSolution(userPuzzle, solvedPuzzle);

            int workingPuzzle[9][9];
            fill_n(&workingPuzzle[0][0], sizeof(workingPuzzle) / sizeof(**workingPuzzle), 0);

            if(userSolution == true) {
                copyPuzzle(userPuzzle, workingPuzzle);
            }
            else {
                copyPuzzle(puzzle, workingPuzzle);
            }

            int candidates[9][9][9];
            fill_n(&candidates[0][0][0], sizeof(candidates) / sizeof(***candidates), 1);

            calculatePossibleCandidates(workingPuzzle, candidates);

            char startPuzzleString[81];
            char startCandidatesString[729];

            puzzleMatrixToString(workingPuzzle, startPuzzleString);
            candidatesMatrixToString(candidates, startCandidatesString);

            cout << "@";
            for(int index = 0; index < 81; index++) {
                cout << startPuzzleString[index];
            }
            cout << "/";
            cout << "#";
            for(int index = 0; index < 729; index++) {
                cout << startCandidatesString[index];
            }
            cout << "/";

            bool solvedStep = false;

            do {
                solvedStep = false;

                calculatePossibleCandidates(workingPuzzle, candidates);

                tuple<bool, tuple<int, int>, int> onlyCandidateSolution;

                onlyCandidateSolution = onlyCandidate(workingPuzzle, candidates);

                if(get<0>(onlyCandidateSolution) == true) {
                    solvedStep = true;

                    workingPuzzle[get<0>(get<1>(onlyCandidateSolution))][get<1>(get<1>(onlyCandidateSolution))] = get<2>(onlyCandidateSolution);

                    printValueMethodProgram("Only candidate", get<1>(onlyCandidateSolution), get<2>(onlyCandidateSolution));
                }
                else {
                    tuple<bool, tuple<int, int>, int> lastPossiblePlaceInRowSolution;

                    lastPossiblePlaceInRowSolution = lastPossiblePlaceInRow(workingPuzzle, candidates);

                    if(get<0>(lastPossiblePlaceInRowSolution) == true) {
                        solvedStep = true;

                        workingPuzzle[get<0>(get<1>(lastPossiblePlaceInRowSolution))][get<1>(get<1>(lastPossiblePlaceInRowSolution))] = get<2>(lastPossiblePlaceInRowSolution);

                        printValueMethodProgram("Last possible place in row", get<1>(lastPossiblePlaceInRowSolution), get<2>(lastPossiblePlaceInRowSolution));
                    }
                    else {
                        tuple<bool, tuple<int, int>, int> lastPossiblePlaceInColumnSolution;

                        lastPossiblePlaceInColumnSolution = lastPossiblePlaceInColumn(workingPuzzle, candidates);

                        if(get<0>(lastPossiblePlaceInColumnSolution) == true) {
                            solvedStep = true;

                            workingPuzzle[get<0>(get<1>(lastPossiblePlaceInColumnSolution))][get<1>(get<1>(lastPossiblePlaceInColumnSolution))] = get<2>(lastPossiblePlaceInColumnSolution);

                            printValueMethodProgram("Last possible place in column", get<1>(lastPossiblePlaceInColumnSolution), get<2>(lastPossiblePlaceInColumnSolution));
                        }
                        else {
                            tuple<bool, tuple<int, int>, int> lastPossiblePlaceInBoxSolution;

                            lastPossiblePlaceInBoxSolution = lastPossiblePlaceInBox(workingPuzzle, candidates);

                            if(get<0>(lastPossiblePlaceInBoxSolution) == true) {
                                solvedStep = true;

                                workingPuzzle[get<0>(get<1>(lastPossiblePlaceInBoxSolution))][get<1>(get<1>(lastPossiblePlaceInBoxSolution))] = get<2>(lastPossiblePlaceInBoxSolution);

                                printValueMethodProgram("Last possible place in box", get<1>(lastPossiblePlaceInBoxSolution), get<2>(lastPossiblePlaceInBoxSolution));
                            }
                            else {
                                tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedPairsInRowSolution;

                                nakedPairsInRowSolution = nakedPairsInRow(workingPuzzle, candidates);

                                if(get<0>(nakedPairsInRowSolution) == true) {
                                    solvedStep = true;

                                    vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                    candidatesToStay = get<1>(nakedPairsInRowSolution);
                                    candidatesToRemove = get<2>(nakedPairsInRowSolution);

                                    for(int index = 0; index < candidatesToRemove.size(); index++) {
                                        candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                    }

                                    printCandidatesMethodProgram("Naked pairs in row", candidatesToStay, candidatesToRemove);
                                }
                                else {
                                    tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedPairsInColumnSolution;

                                    nakedPairsInColumnSolution = nakedPairsInColumn(workingPuzzle, candidates);

                                    if(get<0>(nakedPairsInColumnSolution) == true) {
                                        solvedStep = true;

                                        vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                        vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                        candidatesToStay = get<1>(nakedPairsInColumnSolution);
                                        candidatesToRemove = get<2>(nakedPairsInColumnSolution);

                                        for(int index = 0; index < candidatesToRemove.size(); index++) {
                                            candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                        }

                                        printCandidatesMethodProgram("Naked pairs in column", candidatesToStay, candidatesToRemove);
                                    }
                                    else {
                                        tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedPairsInBoxSolution;

                                        nakedPairsInBoxSolution = nakedPairsInBox(workingPuzzle, candidates);

                                        if(get<0>(nakedPairsInBoxSolution) == true) {
                                            solvedStep = true;

                                            vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                            vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                            candidatesToStay = get<1>(nakedPairsInBoxSolution);
                                            candidatesToRemove = get<2>(nakedPairsInBoxSolution);

                                            for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                            }

                                            printCandidatesMethodProgram("Naked pairs in box", candidatesToStay, candidatesToRemove);
                                        }
                                        else {
                                            tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedTriplesInRowSolution;

                                            nakedTriplesInRowSolution = nakedTriplesInRow(workingPuzzle, candidates);

                                            if(get<0>(nakedTriplesInRowSolution) == true) {
                                                solvedStep = true;

                                                vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                candidatesToStay = get<1>(nakedTriplesInRowSolution);
                                                candidatesToRemove = get<2>(nakedTriplesInRowSolution);

                                                for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                    candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                }

                                                printCandidatesMethodProgram("Naked triples in row", candidatesToStay, candidatesToRemove);
                                            }
                                            else {
                                                tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedTriplesInColumnSolution;

                                                nakedTriplesInColumnSolution = nakedTriplesInColumn(workingPuzzle, candidates);

                                                if(get<0>(nakedTriplesInColumnSolution) == true) {
                                                    solvedStep = true;

                                                    vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                    candidatesToStay = get<1>(nakedTriplesInColumnSolution);
                                                    candidatesToRemove = get<2>(nakedTriplesInColumnSolution);

                                                    for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                        candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                    }

                                                    printCandidatesMethodProgram("Naked triples in column", candidatesToStay, candidatesToRemove);
                                                }
                                                else {
                                                    tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedTriplesInBoxSolution;

                                                    nakedTriplesInBoxSolution = nakedTriplesInBox(workingPuzzle, candidates);

                                                    if(get<0>(nakedTriplesInBoxSolution) == true) {
                                                        solvedStep = true;

                                                        vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                        vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                        candidatesToStay = get<1>(nakedTriplesInBoxSolution);
                                                        candidatesToRemove = get<2>(nakedTriplesInBoxSolution);

                                                        for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                            candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                        }

                                                        printCandidatesMethodProgram("Naked triples in box", candidatesToStay, candidatesToRemove);
                                                    }    
                                                    else {
                                                        tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedQuadsInRowSolution;

                                                        nakedQuadsInRowSolution = nakedQuadsInRow(workingPuzzle, candidates);

                                                        if(get<0>(nakedQuadsInRowSolution) == true) {
                                                            solvedStep = true;

                                                            vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                            vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                            candidatesToStay = get<1>(nakedQuadsInRowSolution);
                                                            candidatesToRemove = get<2>(nakedQuadsInRowSolution);

                                                            for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                            }

                                                            printCandidatesMethodProgram("Naked quads in row", candidatesToStay, candidatesToRemove);
                                                        }
                                                        else {
                                                            tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedQuadsInColumnSolution;

                                                            nakedQuadsInColumnSolution = nakedQuadsInColumn(workingPuzzle, candidates);

                                                            if(get<0>(nakedQuadsInColumnSolution) == true) {
                                                                solvedStep = true;

                                                                vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                candidatesToStay = get<1>(nakedQuadsInColumnSolution);
                                                                candidatesToRemove = get<2>(nakedQuadsInColumnSolution);

                                                                for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                    candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                }

                                                                printCandidatesMethodProgram("Naked quads in column", candidatesToStay, candidatesToRemove);
                                                            }
                                                            else {
                                                                tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedQuadsInBoxSolution;

                                                                nakedQuadsInBoxSolution = nakedQuadsInBox(workingPuzzle, candidates);

                                                                if(get<0>(nakedQuadsInBoxSolution) == true) {
                                                                    solvedStep = true;

                                                                    vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                    candidatesToStay = get<1>(nakedQuadsInBoxSolution);
                                                                    candidatesToRemove = get<2>(nakedQuadsInBoxSolution);

                                                                    for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                        candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                    }

                                                                    printCandidatesMethodProgram("Naked quads in box", candidatesToStay, candidatesToRemove);
                                                                }
                                                                else {
                                                                    tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenPairsInRowSolution;

                                                                    hiddenPairsInRowSolution = hiddenPairsInRow(workingPuzzle, candidates);

                                                                    if(get<0>(hiddenPairsInRowSolution) == true) {
                                                                        solvedStep = true;

                                                                        vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                        vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                        candidatesToStay = get<1>(hiddenPairsInRowSolution);
                                                                        candidatesToRemove = get<2>(hiddenPairsInRowSolution);

                                                                        for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                            candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                        }

                                                                        printCandidatesMethodProgram("Hidden pairs in row", candidatesToStay, candidatesToRemove);
                                                                    }
                                                                    else {
                                                                        tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenPairsInColumnSolution;

                                                                        hiddenPairsInColumnSolution = hiddenPairsInColumn(workingPuzzle, candidates);

                                                                        if(get<0>(hiddenPairsInColumnSolution) == true) {
                                                                            solvedStep = true;

                                                                            vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                            vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                            candidatesToStay = get<1>(hiddenPairsInColumnSolution);
                                                                            candidatesToRemove = get<2>(hiddenPairsInColumnSolution);

                                                                            for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                            }

                                                                            printCandidatesMethodProgram("Hidden pairs in column", candidatesToStay, candidatesToRemove);
                                                                        }
                                                                        else {
                                                                            tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenPairsInBoxSolution;

                                                                            hiddenPairsInBoxSolution = hiddenPairsInBox(workingPuzzle, candidates);

                                                                            if(get<0>(hiddenPairsInBoxSolution) == true) {
                                                                                solvedStep = true;

                                                                                vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                candidatesToStay = get<1>(hiddenPairsInBoxSolution);
                                                                                candidatesToRemove = get<2>(hiddenPairsInBoxSolution);

                                                                                for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                    candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                }

                                                                                printCandidatesMethodProgram("Hidden pairs in box", candidatesToStay, candidatesToRemove);
                                                                            }
                                                                            else {
                                                                                tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenTriplesInRowSolution;

                                                                                hiddenTriplesInRowSolution = hiddenTriplesInRow(workingPuzzle, candidates);

                                                                                if(get<0>(hiddenTriplesInRowSolution) == true) {
                                                                                    solvedStep = true;

                                                                                    vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                    candidatesToStay = get<1>(hiddenTriplesInRowSolution);
                                                                                    candidatesToRemove = get<2>(hiddenTriplesInRowSolution);

                                                                                    for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                        candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                    }

                                                                                    printCandidatesMethodProgram("Hidden triples in row", candidatesToStay, candidatesToRemove);
                                                                                }
                                                                                else {
                                                                                    tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenTriplesInColumnSolution;

                                                                                    hiddenTriplesInColumnSolution = hiddenTriplesInColumn(workingPuzzle, candidates);

                                                                                    if(get<0>(hiddenTriplesInColumnSolution) == true) {
                                                                                        solvedStep = true;

                                                                                        vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                        vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                        candidatesToStay = get<1>(hiddenTriplesInColumnSolution);
                                                                                        candidatesToRemove = get<2>(hiddenTriplesInColumnSolution);

                                                                                        for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                            candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                        }

                                                                                        printCandidatesMethodProgram("Hidden triples in column", candidatesToStay, candidatesToRemove);
                                                                                    }
                                                                                    else {
                                                                                        tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenTriplesInBoxSolution;

                                                                                        hiddenTriplesInBoxSolution = hiddenTriplesInBox(workingPuzzle, candidates);

                                                                                        if(get<0>(hiddenTriplesInBoxSolution) == true) {
                                                                                            solvedStep = true;

                                                                                            vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                            vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                            candidatesToStay = get<1>(hiddenTriplesInBoxSolution);
                                                                                            candidatesToRemove = get<2>(hiddenTriplesInBoxSolution);

                                                                                            for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                            }

                                                                                            printCandidatesMethodProgram("Hidden triples in box", candidatesToStay, candidatesToRemove);
                                                                                        }
                                                                                        else {
                                                                                            tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenQuadsInRowSolution;

                                                                                            hiddenQuadsInRowSolution = hiddenQuadsInRow(workingPuzzle, candidates);

                                                                                            if(get<0>(hiddenQuadsInRowSolution) == true) {
                                                                                                solvedStep = true;

                                                                                                vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                candidatesToStay = get<1>(hiddenQuadsInRowSolution);
                                                                                                candidatesToRemove = get<2>(hiddenQuadsInRowSolution);

                                                                                                for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                    candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                }

                                                                                                printCandidatesMethodProgram("Hidden quads in row", candidatesToStay, candidatesToRemove);
                                                                                            }
                                                                                            else {
                                                                                                tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenQuadsInColumnSolution;

                                                                                                hiddenQuadsInColumnSolution = hiddenQuadsInColumn(workingPuzzle, candidates);

                                                                                                if(get<0>(hiddenQuadsInColumnSolution) == true) {
                                                                                                    solvedStep = true;

                                                                                                    vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                    candidatesToStay = get<1>(hiddenQuadsInColumnSolution);
                                                                                                    candidatesToRemove = get<2>(hiddenQuadsInColumnSolution);

                                                                                                    for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                        candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                    }

                                                                                                    printCandidatesMethodProgram("Hidden quads in column", candidatesToStay, candidatesToRemove);
                                                                                                }
                                                                                                else {
                                                                                                    tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenQuadsInBoxSolution;

                                                                                                    hiddenQuadsInBoxSolution = hiddenQuadsInBox(workingPuzzle, candidates);

                                                                                                    if(get<0>(hiddenQuadsInBoxSolution) == true) {
                                                                                                        solvedStep = true;

                                                                                                        vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                        vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                        candidatesToStay = get<1>(hiddenQuadsInBoxSolution);
                                                                                                        candidatesToRemove = get<2>(hiddenQuadsInBoxSolution);

                                                                                                        for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                            candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                        }

                                                                                                        printCandidatesMethodProgram("Hidden quads in box", candidatesToStay, candidatesToRemove);
                                                                                                    }
                                                                                                    else {
                                                                                                        tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> boxRowReductionSolution;

                                                                                                        boxRowReductionSolution = boxRowReduction(workingPuzzle, candidates);

                                                                                                        if(get<0>(boxRowReductionSolution) == true) {
                                                                                                            solvedStep = true;

                                                                                                            vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                            vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                            candidatesToStay = get<1>(boxRowReductionSolution);
                                                                                                            candidatesToRemove = get<2>(boxRowReductionSolution);

                                                                                                            for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                                candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                            }

                                                                                                            printCandidatesMethodProgram("Box row reduction", candidatesToStay, candidatesToRemove);
                                                                                                        }
                                                                                                        else {
                                                                                                            tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> boxColumnReductionSolution;

                                                                                                            boxColumnReductionSolution = boxColumnReduction(workingPuzzle, candidates);

                                                                                                            if(get<0>(boxColumnReductionSolution) == true) {
                                                                                                                solvedStep = true;

                                                                                                                vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                                vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                                candidatesToStay = get<1>(boxColumnReductionSolution);
                                                                                                                candidatesToRemove = get<2>(boxColumnReductionSolution);

                                                                                                                for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                                    candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                                }

                                                                                                                printCandidatesMethodProgram("Box column reduction", candidatesToStay, candidatesToRemove);
                                                                                                            }
                                                                                                            else {
                                                                                                                tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> rowBoxReductionSolution;

                                                                                                                rowBoxReductionSolution = rowBoxReduction(workingPuzzle, candidates);

                                                                                                                if(get<0>(rowBoxReductionSolution) == true) {
                                                                                                                    solvedStep = true;

                                                                                                                    vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                                    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                                    candidatesToStay = get<1>(rowBoxReductionSolution);
                                                                                                                    candidatesToRemove = get<2>(rowBoxReductionSolution);

                                                                                                                    for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                                        candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                                    }           

                                                                                                                    printCandidatesMethodProgram("Row box reduction", candidatesToStay, candidatesToRemove);                                                                                                  
                                                                                                                }
                                                                                                                else {
                                                                                                                    tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> columnBoxReductionSolution;

                                                                                                                    columnBoxReductionSolution = columnBoxReduction(workingPuzzle, candidates);

                                                                                                                    if(get<0>(columnBoxReductionSolution) == true) {
                                                                                                                        solvedStep = true;

                                                                                                                        vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                                        vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                                        candidatesToStay = get<1>(columnBoxReductionSolution);
                                                                                                                        candidatesToRemove = get<2>(columnBoxReductionSolution);

                                                                                                                        for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                                            candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                                        }           

                                                                                                                        printCandidatesMethodProgram("Column box reduction", candidatesToStay, candidatesToRemove);                                                                                                                                                                                                                   
                                                                                                                    }
                                                                                                                    else {
                                                                                                                        tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> xWingRowSolution;

                                                                                                                        xWingRowSolution = xWingRow(workingPuzzle, candidates);

                                                                                                                        if(get<0>(xWingRowSolution) == true) {
                                                                                                                            solvedStep = true;

                                                                                                                            vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                                            vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                                            candidatesToStay = get<1>(xWingRowSolution);
                                                                                                                            candidatesToRemove = get<2>(xWingRowSolution);

                                                                                                                            for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                                                candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                                            }

                                                                                                                            printCandidatesMethodProgram("X wing row", candidatesToStay, candidatesToRemove);
                                                                                                                        }
                                                                                                                        else {
                                                                                                                            tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> xWingColumnSolution;

                                                                                                                            xWingColumnSolution = xWingColumn(workingPuzzle, candidates);

                                                                                                                            if(get<0>(xWingColumnSolution) == true) {
                                                                                                                                solvedStep = true;

                                                                                                                                vector<tuple<tuple<int, int>, int>> candidatesToStay;
                                                                                                                                vector<tuple<tuple<int, int>, int>> candidatesToRemove;

                                                                                                                                candidatesToStay = get<1>(xWingColumnSolution);
                                                                                                                                candidatesToRemove = get<2>(xWingColumnSolution);

                                                                                                                                for(int index = 0; index < candidatesToRemove.size(); index++) {
                                                                                                                                    candidates[get<0>(get<0>(candidatesToRemove[index]))][get<1>(get<0>(candidatesToRemove[index]))][get<1>(candidatesToRemove[index])] = 0;
                                                                                                                                }

                                                                                                                                printCandidatesMethodProgram("X wing column", candidatesToStay, candidatesToRemove);
                                                                                                                            }
                                                                                                                            else {
                                                                                                                                // new strategy
                                                                                                                            }
                                                                                                                        }
                                                                                                                    }
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                } 
            }while(solvedStep == true);

            break;
        }

        default: {
            break;
        }
    }

    return 0;
}



void puzzleStringToMatrix(char *puzzleString, int puzzle[9][9]) {
    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            puzzle[index1][index2] = characterToInteger(puzzleString[index1 * 9 + index2]);
        } 
    }
}

void candidatesStringToMatrix(char *candidatesString, int candidates[9][9][9]) {
    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            for(int index3 = 0; index3 < 9; index3++) {
                candidates[index1][index2][index3] = characterToInteger(candidatesString[index1 * 81 + index2 * 9 + index3]);
            } 
        } 
    } 
}

void puzzleMatrixToString(int puzzle[9][9], char puzzleString[81]) {
    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            puzzleString[index1 * 9 + index2] = integerToCharacter(puzzle[index1][index2]);
        }
    }
}

void candidatesMatrixToString(int candidates[9][9][9], char candidatesString[729]) {
    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            for(int index3 = 0; index3 < 9; index3++) {
                candidatesString[index1 * 81 + index2 * 9 + index3] = integerToCharacter(candidates[index1][index2][index3]);
            }
        }
    }
}



bool comparePuzzles(int puzzle1[9][9], int puzzle2[9][9]) {
    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            if(puzzle1[index1][index2] != puzzle2[index1][index2]) {
                return false;
            }
        }
    }

    return true;
}

void copyPuzzle(int puzzleSource[9][9], int puzzleDestination[9][9]) {
    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            puzzleDestination[index1][index2] = puzzleSource[index1][index2];
        }
    }
}



bool checkUserSolution(int userSolution[9][9], int puzzleSolution[9][9]) {
    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            if(userSolution[index1][index2] != 0) {
                if(userSolution[index1][index2] != puzzleSolution[index1][index2]) {
                    return false;
                }
            }
        }
    }

    return true;
}



void printPuzzle(int puzzle[9][9])
{
    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            cout << puzzle[index1][index2];

            if(index2 == 2 || index2 == 5) {
                cout << "|";
            }
        }

        cout << endl;
        if(index1 == 2 || index1 == 5) {
            cout << "-----------";
            cout << endl;
        }
    }
}

void printCandidates(int candidates[9][9][9]) {
    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            for(int index3 = 0; index3 < 3; index3++) {
                cout << candidates[index1][index2][index3];
            }

            if(index2 != 8) {
                cout << "|";
            }
        }

        cout << endl;

        for(int index2 = 0; index2 < 9; index2++) {
            for(int index3 = 3; index3 < 6; index3++) {
                cout << candidates[index1][index2][index3];
            }

            if(index2 != 8) {
                cout << "|";
            }
        }

        cout << endl;

        for(int index2 = 0; index2 < 9; index2++) {
            for(int index3 = 6; index3 < 9; index3++) {
                cout << candidates[index1][index2][index3];
            }

            if(index2 != 8) {
                cout << "|";
            }
        }

        cout << endl;

        if(index1 != 8) {
            cout << "-----------------------------------";
            cout << endl;
        }
    }
}



void printValueMethodHuman(string name, tuple<int, int> coordinates, int value) {
    cout << "--------------------------" << endl;
    cout << name << endl;
    cout << get<0>(coordinates) << " " << get<1>(coordinates) << " " << value << endl;
    cout << "--------------------------" << endl;
}

void printCandidatesMethodHuman(string name, vector<tuple<tuple<int, int>, int>> candidatesToStay, vector<tuple<tuple<int, int>, int>> candidatesToRemove) {
    cout << "--------------------------" << endl;
    cout << name << endl;
    cout << "Candidates to stay" << endl;

    for(int index = 0; index < candidatesToStay.size(); index++) {
        cout << get<0>(get<0>(candidatesToStay[index])) << " " << get<1>(get<0>(candidatesToStay[index])) << " " << get<1>(candidatesToStay[index]) << endl;
    }

    cout << "Candidates to remove" << endl;

    for(int index = 0; index < candidatesToRemove.size(); index++) {
        cout << get<0>(get<0>(candidatesToRemove[index])) << " " << get<1>(get<0>(candidatesToRemove[index])) << " " << get<1>(candidatesToRemove[index]) << endl;
    }

    cout << "--------------------------" << endl;
}

void printValueMethodProgram(string name, tuple<int, int> coordinates, int value) {
    cout << "*" << name << "/";
    cout << "%" << get<0>(coordinates) << get<1>(coordinates) << value << "/";
}

void printCandidatesMethodProgram(string name, vector<tuple<tuple<int, int>, int>> candidatesToStay, vector<tuple<tuple<int, int>, int>> candidatesToRemove) {
    cout << "*" << name << "/";

    for(int index = 0; index < candidatesToStay.size(); index++) {
        cout << "+" << get<0>(get<0>(candidatesToStay[index])) << get<1>(get<0>(candidatesToStay[index])) << get<1>(candidatesToStay[index]) << "/";
    }

    for(int index = 0; index < candidatesToRemove.size(); index++) {
        cout << "-" << get<0>(get<0>(candidatesToRemove[index])) << get<1>(get<0>(candidatesToRemove[index])) << get<1>(candidatesToRemove[index]) << "/";
    }
}



int characterToInteger(char character) {
    int integer;

    integer = character - '0';

    return integer;
}

char integerToCharacter(int integer) {
    char character;

    character = '0' + integer;

    return character;
}



void getPuzzleRow(int puzzle[9][9], int rowIndex, int row[9]) {
    for(int index = 0; index < 9; index++) {
        row[index] = puzzle[rowIndex][index];
    }
}

void getPuzzleColumn(int puzzle[9][9], int columnIndex, int column[9]) {
    for(int index = 0; index < 9; index++) {
        column[index] = puzzle[index][columnIndex];
    }
}

void getPuzzleBox(int puzzle[9][9], int rowIndex, int columnIndex, int box[3][3]) {
    int boxStartRow = rowIndex - rowIndex % 3;
    int boxStartColumn = columnIndex - columnIndex % 3;

    for(int index1 = 0; index1 < 3; index1++) {
        for(int index2 = 0; index2 < 3; index2++) {
            box[index1][index2] = puzzle[boxStartRow + index1][boxStartColumn + index2];
        }
    }
}

void getCandidatesRow(int candidates[9][9][9], int rowIndex, int row[9][9]) {
    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            row[index1][index2] = candidates[rowIndex][index1][index2];
        }
    }
}

void getCandidatesColumn(int candidates[9][9][9], int columnIndex, int column[9][9]) {
    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            column[index1][index2] = candidates[index1][columnIndex][index2];
        }
    }
}

void getCandidatesBox(int candidates[9][9][9], int rowIndex, int columnIndex, int box[3][3][9]) {
    int boxStartRow = rowIndex - rowIndex % 3;
    int boxStartColumn = columnIndex - columnIndex % 3;

    for(int index1 = 0; index1 < 3; index1++) {
        for(int index2 = 0; index2 < 3; index2++) {
            for(int index3 = 0; index3 < 9; index3++) {
                box[index1][index2][index3] = candidates[boxStartRow + index1][boxStartColumn + index2][index3];
            }
        }
    }
}



bool checkForUniqueSolution(int puzzle[9][9]) {
    int solution1[9][9], solution2[9][9];
    fill_n(&solution1[0][0], sizeof(solution1) / sizeof(**solution1), 0);
    fill_n(&solution2[0][0], sizeof(solution2) / sizeof(**solution2), 0);

    copyPuzzle(puzzle, solution1);
    copyPuzzle(puzzle, solution2);

    if(solveSudoku(solution1, 0, 0, false, NULL) == true) {
        if(solveSudoku(solution2, 0, 0, true, solution1) == true) {
            return false;
        }
    }
    else {
        return false;
    }

    return true;
}



bool solveSudoku(int puzzle[9][9], int rowIndex, int columnIndex, bool avoidSolution, int solutionToAvoid[9][9]) {
    if(avoidSolution == true) {
        if(comparePuzzles(puzzle, solutionToAvoid) == true) {
            return false;
        }
    }

    if (rowIndex == 8 && columnIndex == 9) {
        return true;
    }

    if (columnIndex == 9) {
        rowIndex++;
        columnIndex = 0;
    }

    if (puzzle[rowIndex][columnIndex] > 0)
        return solveSudoku(puzzle, rowIndex, columnIndex + 1, avoidSolution, solutionToAvoid);
 
    for (int number = 1; number <= 9; number++) 
    {
        if (isSafe(puzzle, rowIndex, columnIndex, number)) 
        {
            puzzle[rowIndex][columnIndex] = number;
           
            if (solveSudoku(puzzle, rowIndex, columnIndex + 1, avoidSolution, solutionToAvoid))
                return true;
        }
        puzzle[rowIndex][columnIndex] = 0;
    }

    return false;
}

bool isSafe(int puzzle[9][9], int rowIndex, int columnIndex, int number) {
    int row[9];
    fill_n(&row[0], sizeof(row) / sizeof(*row), 0);

    getPuzzleRow(puzzle, rowIndex, row);

    for(int index = 0; index < 9; index++) {
        if(row[index] == number) {
            return false;
        }
    }

    int column[9];
    fill_n(&column[0], sizeof(column) / sizeof(*column), 0);

    getPuzzleColumn(puzzle, columnIndex, column);

    for(int index = 0; index < 9; index++) {
        if(column[index] == number) {
            return false;
        }
    }

    int box[3][3];
    fill_n(&box[0][0], sizeof(box) / sizeof(**box), 0);

    getPuzzleBox(puzzle, rowIndex, columnIndex, box);
   
    for(int index1 = 0; index1 < 3; index1++) {
        for(int index2 = 0; index2 < 3; index2++) {
            if(box[index1][index2] == number) { 
                return false;
            }
        }
    }
 
    return true;
}



void calculatePossibleCandidates(int puzzle[9][9], int candidates[9][9][9]) {
    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            if(puzzle[index1][index2] != 0) {
                for(int number = 1; number <= 9; number++) {
                    candidates[index1][index2][number - 1] = 0;
                }
            }
            else {
                int row[9];
                fill_n(&row[0], sizeof(row) / sizeof(*row), 0);

                getPuzzleRow(puzzle, index1, row);

                for(int index3 = 0; index3 < 9; index3++) {
                    if(row[index3] != 0) {
                        candidates[index1][index2][row[index3] - 1] = 0;
                    }
                }

                int column[9];
                fill_n(&column[0], sizeof(column) / sizeof(*column), 0);

                getPuzzleColumn(puzzle, index2, column);

                for(int index3 = 0; index3 < 9; index3++) {
                    if(column[index3] != 0) {
                        candidates[index1][index2][column[index3] - 1] = 0;
                    }
                }

                int box[3][3];
                fill_n(&box[0][0], sizeof(box) / sizeof(**box), 0);

                getPuzzleBox(puzzle, index1, index2, box);

                for(int index3 = 0; index3 < 3; index3++) {
                    for(int index4 = 0; index4 < 3; index4++) {
                        if(box[index3][index4] != 0) {
                            candidates[index1][index2][box[index3][index4] - 1] = 0;
                        }
                    }
                }
            }
        }
    }
}



tuple<bool, tuple<int, int>, int> onlyCandidate(int puzzle[9][9], int candidates[9][9][9]) {
    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            if(puzzle[index1][index2] == 0) {
                int counter = 0;
                int position = 0;

                for(int index3 = 0; index3 < 9; index3++) {
                    if(candidates[index1][index2][index3] == 1) {
                        counter++;
                        position = index3;
                    }
                }

                if(counter == 1) {
                    return make_tuple(true, make_tuple(index1, index2), position + 1);
                }
            }
        }
    }

    return make_tuple(false, make_tuple(-1, -1), -1);
}

tuple<bool, tuple<int, int>, int> lastPossiblePlaceInRow(int puzzle[9][9], int candidates[9][9][9]) {
    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            if(puzzle[index1][index2] == 0) {
                int candidatesRow[9][9];
                fill_n(&candidatesRow[0][0], sizeof(candidatesRow) / sizeof(**candidatesRow), 0);

                getCandidatesRow(candidates, index1, candidatesRow);

                for(int index3 = 0; index3 < 9; index3++) {
                    int candidateCounter = 0;

                    if(candidatesRow[index2][index3] == 1) {
                        for(int index4 = 0; index4 < 9; index4++) {
                            if(index4 != index2) {
                                if(candidatesRow[index4][index3] == 1) {
                                    candidateCounter++;
                                }
                            }
                        }

                        if(candidateCounter == 0) {
                            return make_tuple(true, make_tuple(index1, index2), index3 + 1);
                        }
                    }
                }
            }
        }
    }

    return make_tuple(false, make_tuple(-1, -1), -1);
}

tuple<bool, tuple<int, int>, int> lastPossiblePlaceInColumn(int puzzle[9][9], int candidates[9][9][9]) {
    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            if(puzzle[index1][index2] == 0) {
                int candidatesColumn[9][9];
                fill_n(&candidatesColumn[0][0], sizeof(candidatesColumn) / sizeof(**candidatesColumn), 0);

                getCandidatesColumn(candidates, index2, candidatesColumn);

                for(int index3 = 0; index3 < 9; index3++) {
                    int candidateCounter = 0;

                    if(candidatesColumn[index1][index3] == 1) {
                        for(int index4 = 0; index4 < 9; index4++) {
                            if(index4 != index1) {
                                if(candidatesColumn[index4][index3] == 1) {
                                    candidateCounter++;
                                }
                            }
                        }

                        if(candidateCounter == 0) {
                            return make_tuple(true, make_tuple(index1, index2), index3 + 1);
                        }
                    }
                }
            }
        }
    }

    return make_tuple(false, make_tuple(-1, -1), -1);
}

tuple<bool, tuple<int, int>, int> lastPossiblePlaceInBox(int puzzle[9][9], int candidates[9][9][9]) {
    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            if(puzzle[index1][index2] == 0) {
                int candidatesBox[3][3][9];
                fill_n(&candidatesBox[0][0][0], sizeof(candidatesBox) / sizeof(***candidatesBox), 0);

                getCandidatesBox(candidates, index1, index2, candidatesBox);

                for(int index3 = 0; index3 < 9; index3++) {
                    int candidateCounter = 0;

                    if(candidatesBox[index1 % 3][index2 % 3][index3] == 1) {
                        for(int index4 = 0; index4 < 3; index4++) {
                            for(int index5 = 0; index5 < 3; index5++) {
                                if(index4 % 3 != index1 % 3 || index5 % 3 != index2 % 3) {
                                    if(candidatesBox[index4][index5][index3] == 1) {
                                        candidateCounter++;
                                    }
                                }
                            }
                        }

                        if(candidateCounter == 0) {
                            return make_tuple(true, make_tuple(index1, index2), index3 + 1);
                        }
                    }
                }
            }
        }
    }

    return make_tuple(false, make_tuple(-1, -1), -1);
}



tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedPairsInRow(int puzzle[9][9], int candidates[9][9][9]) {
   vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            if(puzzle[index1][index2] == 0) {
                int candidatesRow[9][9];
                fill_n(&candidatesRow[0][0], sizeof(candidatesRow) / sizeof(**candidatesRow), 0);

                getCandidatesRow(candidates, index1, candidatesRow);

                vector<int> addedCandidates;

                int candidatesToStayCounter1 = 0;
                int candidatesAddedCounter1 = 0;

                for(int index3 = 0; index3 < 9; index3++) {
                    if(candidatesRow[index2][index3] == 1) {
                        candidatesToStayCounter1++;

                        candidatesToStay.push_back(make_tuple(make_tuple(index1, index2), index3));

                        bool candidateAdded = false;

                        for(int index4 = 0; index4 < addedCandidates.size(); index4++) {
                            if(addedCandidates[index4] == index3) {
                                candidateAdded = true;
                            }
                        }

                        if(candidateAdded == false) {
                            candidatesAddedCounter1++;

                            addedCandidates.push_back(index3);
                        }
                    }
                }

                if(candidatesToStayCounter1 == 2 && addedCandidates.size() == 2) {
                    for(int index3 = index2 + 1; index3 < 9; index3++) {
                        int candidatesToStayCounter2 = 0;
                        int candidatesAddedCounter2 = 0;

                        for(int index4 = 0; index4 < 9; index4++) {
                            if(candidatesRow[index3][index4] == 1) {
                                candidatesToStayCounter2++;

                                candidatesToStay.push_back(make_tuple(make_tuple(index1, index3), index4));

                                bool candidateAdded = false;

                                for(int index5 = 0; index5 < addedCandidates.size(); index5++) {
                                    if(addedCandidates[index5] == index4) {
                                        candidateAdded = true;
                                    }
                                }

                                if(candidateAdded == false) {
                                    candidatesAddedCounter2++;

                                    addedCandidates.push_back(index4);
                                }
                            }
                        }

                        if(candidatesToStayCounter2 == 2 && addedCandidates.size() == 2) {
                            for(int index4 = 0; index4 < 9; index4++) {
                                if(index4 != index2 && index4 != index3) {
                                    for(int index5 = 0; index5 < addedCandidates.size(); index5++) {
                                        if(candidatesRow[index4][addedCandidates[index5]] == 1) {
                                            candidatesToRemove.push_back(make_tuple(make_tuple(index1, index4), addedCandidates[index5]));
                                        }
                                    }             
                                }
                            }

                            if(candidatesToRemove.size() > 0) {
                                return make_tuple(true, candidatesToStay, candidatesToRemove);
                            }
                        }

                        for(int index4 = 0; index4 < candidatesToStayCounter2; index4++) {
                            candidatesToStay.pop_back();
                        }

                        for(int index4 = 0; index4 < candidatesAddedCounter2; index4++) {
                            addedCandidates.pop_back();
                        }
                    }
                }

                for(int index3 = 0; index3 < candidatesToStayCounter1; index3++) {
                    candidatesToStay.pop_back();
                }

                for(int index3 = 0; index3 < candidatesAddedCounter1; index3++) {
                    addedCandidates.pop_back();
                }
            }
        }
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedPairsInColumn(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            if(puzzle[index1][index2] == 0) {
                int candidatesColumn[9][9];
                fill_n(&candidatesColumn[0][0], sizeof(candidatesColumn) / sizeof(**candidatesColumn), 0);

                getCandidatesColumn(candidates, index2, candidatesColumn);

                vector<int> addedCandidates;

                int candidatesToStayCounter1 = 0;
                int candidatesAddedCounter1 = 0;

                for(int index3 = 0; index3 < 9; index3++) {
                    if(candidatesColumn[index1][index3] == 1) {
                        candidatesToStayCounter1++;

                        candidatesToStay.push_back(make_tuple(make_tuple(index1, index2), index3));

                        bool candidateAdded = false;

                        for(int index4 = 0; index4 < addedCandidates.size(); index4++) {
                            if(addedCandidates[index4] == index3) {
                                candidateAdded = true;
                            }
                        }

                        if(candidateAdded == false) {
                            candidatesAddedCounter1++;

                            addedCandidates.push_back(index3);
                        }
                    }
                }

                if(candidatesToStayCounter1 == 2 && addedCandidates.size() == 2) {
                    for(int index3 = index1 + 1; index3 < 9; index3++) {
                        int candidatesToStayCounter2 = 0;
                        int candidatesAddedCounter2 = 0;

                        for(int index4 = 0; index4 < 9; index4++) {
                            if(candidatesColumn[index3][index4] == 1) {
                                candidatesToStayCounter2++;

                                candidatesToStay.push_back(make_tuple(make_tuple(index3, index2), index4));

                                bool candidateAdded = false;

                                for(int index5 = 0; index5 < addedCandidates.size(); index5++) {
                                    if(addedCandidates[index5] == index4) {
                                        candidateAdded = true;
                                    }
                                }

                                if(candidateAdded == false) {
                                    candidatesAddedCounter2++;

                                    addedCandidates.push_back(index4);
                                }
                            }
                        }

                        if(candidatesToStayCounter2 == 2 && addedCandidates.size() == 2) {
                            for(int index4 = 0; index4 < 9; index4++) {
                                if(index4 != index1 && index4 != index3) {
                                    for(int index5 = 0; index5 < addedCandidates.size(); index5++) {
                                        if(candidatesColumn[index4][addedCandidates[index5]] == 1) {
                                            candidatesToRemove.push_back(make_tuple(make_tuple(index4, index2), addedCandidates[index5]));
                                        }
                                    }             
                                }
                            }

                            if(candidatesToRemove.size() > 0) {
                                return make_tuple(true, candidatesToStay, candidatesToRemove);
                            }
                        }

                        for(int index4 = 0; index4 < candidatesToStayCounter2; index4++) {
                            candidatesToStay.pop_back();
                        }

                        for(int index4 = 0; index4 < candidatesAddedCounter2; index4++) {
                            addedCandidates.pop_back();
                        }
                    }
                }

                for(int index3 = 0; index3 < candidatesToStayCounter1; index3++) {
                    candidatesToStay.pop_back();
                }

                for(int index3 = 0; index3 < candidatesAddedCounter1; index3++) {
                    addedCandidates.pop_back();
                }
            }
        }
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedPairsInBox(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            if(puzzle[index1][index2] == 0) {
                int candidatesBox[3][3][9];
                fill_n(&candidatesBox[0][0][0], sizeof(candidatesBox) / sizeof(***candidatesBox), 0);

                getCandidatesBox(candidates, index1, index2, candidatesBox);

                vector<int> addedCandidates;

                int candidatesToStayCounter1 = 0;
                int candidatesAddedCounter1 = 0;

                for(int index3 = 0; index3 < 9; index3++) {
                    if(candidatesBox[index1 % 3][index2 % 3][index3] == 1) {
                        candidatesToStayCounter1++;

                        candidatesToStay.push_back(make_tuple(make_tuple(index1, index2), index3));

                        bool candidateAdded = false;

                        for(int index4 = 0; index4 < addedCandidates.size(); index4++) {
                            if(addedCandidates[index4] == index3) {
                                candidateAdded = true;
                            }
                        }

                        if(candidateAdded == false) {
                            candidatesAddedCounter1++;

                            addedCandidates.push_back(index3);
                        }
                    }
                }

                if(candidatesToStayCounter1 == 2 && addedCandidates.size() == 2) {
                    for(int index3 = (index1 % 3) * 3 + index2 % 3 + 1; index3 < 9; index3++) {
                        int candidatesToStayCounter2 = 0;
                        int candidatesAddedCounter2 = 0;

                        for(int index4 = 0; index4 < 9; index4++) {
                            if(candidatesBox[index3 / 3][index3 % 3][index4] == 1) {
                                candidatesToStayCounter2++;

                                candidatesToStay.push_back(make_tuple(make_tuple(index1 - index1 % 3 + index3 / 3, index2 - index2 % 3 + index3 % 3), index4));

                                bool candidateAdded = false;

                                for(int index5 = 0; index5 < addedCandidates.size(); index5++) {
                                    if(addedCandidates[index5] == index4) {
                                        candidateAdded = true;
                                    }
                                }

                                if(candidateAdded == false) {
                                    candidatesAddedCounter2++;

                                    addedCandidates.push_back(index4);
                                }
                            }
                        }

                        if(candidatesToStayCounter2 == 2 && addedCandidates.size() == 2) {
                            for(int index4 = 0; index4 < 9; index4++) {
                                if(index4 != index1 % 3 * 3 + index2 % 3 && index4 != index3) {
                                    for(int index5 = 0; index5 < addedCandidates.size(); index5++) {
                                        if(candidatesBox[index4 / 3][index4 % 3][addedCandidates[index5]] == 1) {
                                            candidatesToRemove.push_back(make_tuple(make_tuple(index1 - index1 % 3 + index4 / 3, index2 - index2 % 3 + index4 % 3), addedCandidates[index5]));
                                        }
                                    }             
                                }
                            }

                            if(candidatesToRemove.size() > 0) {
                                return make_tuple(true, candidatesToStay, candidatesToRemove);
                            }    
                        }

                        for(int index4 = 0; index4 < candidatesToStayCounter2; index4++) {
                            candidatesToStay.pop_back();
                        }

                        for(int index4 = 0; index4 < candidatesAddedCounter2; index4++) {
                            addedCandidates.pop_back();
                        }
                    }
                }

                for(int index3 = 0; index3 < candidatesToStayCounter1; index3++) {
                    candidatesToStay.pop_back();
                }

                for(int index3 = 0; index3 < candidatesAddedCounter1; index3++) {
                    addedCandidates.pop_back();
                }
            }
        }
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}



tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedTriplesInRow(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            if(puzzle[index1][index2] == 0) {
                int candidatesRow[9][9];
                fill_n(&candidatesRow[0][0], sizeof(candidatesRow) / sizeof(**candidatesRow), 0);

                getCandidatesRow(candidates, index1, candidatesRow);

                vector<int> addedCandidates;

                int candidatesToStayCounter1 = 0;
                int candidatesAddedCounter1 = 0;

                for(int index3 = 0; index3 < 9; index3++) {
                    if(candidatesRow[index2][index3] == 1) {
                        candidatesToStayCounter1++;

                        candidatesToStay.push_back(make_tuple(make_tuple(index1, index2), index3));

                        bool candidateAdded = false;

                        for(int index4 = 0; index4 < addedCandidates.size(); index4++) {
                            if(addedCandidates[index4] == index3) {
                                candidateAdded = true;
                            }
                        }

                        if(candidateAdded == false) {
                            candidatesAddedCounter1++;

                            addedCandidates.push_back(index3);
                        }
                    }
                }

                if(candidatesToStayCounter1 > 0 && addedCandidates.size() >= 1 && addedCandidates.size() <= 3) {
                    for(int index3 = index2 + 1; index3 < 9; index3++) {
                        int candidatesToStayCounter2 = 0;
                        int candidatesAddedCounter2 = 0;

                        for(int index4 = 0; index4 < 9; index4++) {
                            if(candidatesRow[index3][index4] == 1) {
                                candidatesToStayCounter2++;

                                candidatesToStay.push_back(make_tuple(make_tuple(index1, index3), index4));

                                bool candidateAdded = false;

                                for(int index5 = 0; index5 < addedCandidates.size(); index5++) {
                                    if(addedCandidates[index5] == index4) {
                                        candidateAdded = true;
                                    }
                                }

                                if(candidateAdded == false) {
                                    candidatesAddedCounter2++;

                                    addedCandidates.push_back(index4);
                                }
                            }
                        }

                        if(candidatesToStayCounter2 > 0 && addedCandidates.size() >= 1 && addedCandidates.size() <= 3) {
                            for(int index4 = index3 + 1; index4 < 9; index4++) {
                                int candidatesToStayCounter3 = 0;
                                int candidatesAddedCounter3 = 0;

                                for(int index5 = 0; index5 < 9; index5++) {
                                    if(candidatesRow[index4][index5] == 1) {
                                        candidatesToStayCounter3++;

                                        candidatesToStay.push_back(make_tuple(make_tuple(index1, index4), index5));

                                        bool candidateAdded = false;

                                        for(int index6 = 0; index6 < addedCandidates.size(); index6++) {
                                            if(addedCandidates[index6] == index5) {
                                                candidateAdded = true;
                                            }
                                        }

                                        if(candidateAdded == false) {
                                            candidatesAddedCounter3++;

                                            addedCandidates.push_back(index5);
                                        }
                                    }
                                }

                                if(candidatesToStayCounter3 > 0 && addedCandidates.size() == 3) {
                                    for(int index5 = 0; index5 < 9; index5++) {
                                        if(index5 != index2 && index5 != index3 && index5 != index4) {
                                            for(int index6 = 0; index6 < addedCandidates.size(); index6++) {
                                                if(candidatesRow[index5][addedCandidates[index6]] == 1) {
                                                    candidatesToRemove.push_back(make_tuple(make_tuple(index1, index5), addedCandidates[index6]));
                                                }
                                            }             
                                        }
                                    }

                                    if(candidatesToRemove.size() > 0) {
                                        return make_tuple(true, candidatesToStay, candidatesToRemove);
                                    }
                                }

                                for(int index5 = 0; index5 < candidatesToStayCounter3; index5++) {
                                    candidatesToStay.pop_back();
                                }

                                for(int index5 = 0; index5 < candidatesAddedCounter3; index5++) {
                                    addedCandidates.pop_back();
                                }
                            }
                        }

                        for(int index4 = 0; index4 < candidatesToStayCounter2; index4++) {
                            candidatesToStay.pop_back();
                        }

                        for(int index4 = 0; index4 < candidatesAddedCounter2; index4++) {
                            addedCandidates.pop_back();
                        }
                    }
                }

                for(int index3 = 0; index3 < candidatesToStayCounter1; index3++) {
                    candidatesToStay.pop_back();
                }

                for(int index3 = 0; index3 < candidatesAddedCounter1; index3++) {
                    addedCandidates.pop_back();
                }
            }
        }
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedTriplesInColumn(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            if(puzzle[index1][index2] == 0) {
                int candidatesColumn[9][9];
                fill_n(&candidatesColumn[0][0], sizeof(candidatesColumn) / sizeof(**candidatesColumn), 0);

                getCandidatesColumn(candidates, index2, candidatesColumn);

                vector<int> addedCandidates;

                int candidatesToStayCounter1 = 0;
                int candidatesAddedCounter1 = 0;

                for(int index3 = 0; index3 < 9; index3++) {
                    if(candidatesColumn[index1][index3] == 1) {
                        candidatesToStayCounter1++;

                        candidatesToStay.push_back(make_tuple(make_tuple(index1, index2), index3));

                        bool candidateAdded = false;

                        for(int index4 = 0; index4 < addedCandidates.size(); index4++) {
                            if(addedCandidates[index4] == index3) {
                                candidateAdded = true;
                            }
                        }

                        if(candidateAdded == false) {
                            candidatesAddedCounter1++;

                            addedCandidates.push_back(index3);
                        }
                    }
                }

                if(candidatesToStayCounter1 > 0 && addedCandidates.size() >= 1 && addedCandidates.size() <= 3) {
                    for(int index3 = index1 + 1; index3 < 9; index3++) {
                        int candidatesToStayCounter2 = 0;
                        int candidatesAddedCounter2 = 0;

                        for(int index4 = 0; index4 < 9; index4++) {
                            if(candidatesColumn[index3][index4] == 1) {
                                candidatesToStayCounter2++;

                                candidatesToStay.push_back(make_tuple(make_tuple(index3, index2), index4));

                                bool candidateAdded = false;

                                for(int index5 = 0; index5 < addedCandidates.size(); index5++) {
                                    if(addedCandidates[index5] == index4) {
                                        candidateAdded = true;
                                    }
                                }

                                if(candidateAdded == false) {
                                    candidatesAddedCounter2++;

                                    addedCandidates.push_back(index4);
                                }
                            }
                        }

                        if(candidatesToStayCounter2 > 0 && addedCandidates.size() >= 1 && addedCandidates.size() <= 3) {
                            for(int index4 = index3 + 1; index4 < 9; index4++) {
                                int candidatesToStayCounter3 = 0;
                                int candidatesAddedCounter3 = 0;

                                for(int index5 = 0; index5 < 9; index5++) {
                                    if(candidatesColumn[index4][index5] == 1) {
                                        candidatesToStayCounter3++;

                                        candidatesToStay.push_back(make_tuple(make_tuple(index4, index2), index5));

                                        bool candidateAdded = false;

                                        for(int index6 = 0; index6 < addedCandidates.size(); index6++) {
                                            if(addedCandidates[index6] == index5) {
                                                candidateAdded = true;
                                            }
                                        }

                                        if(candidateAdded == false) {
                                            candidatesAddedCounter3++;

                                            addedCandidates.push_back(index5);
                                        }
                                    }
                                }

                                if(candidatesToStayCounter3 > 0 && addedCandidates.size() == 3) {
                                    for(int index5 = 0; index5 < 9; index5++) {
                                        if(index5 != index1 && index5 != index3 && index5 != index4) {
                                            for(int index6 = 0; index6 < addedCandidates.size(); index6++) {
                                                if(candidatesColumn[index5][addedCandidates[index6]] == 1) {
                                                    candidatesToRemove.push_back(make_tuple(make_tuple(index5, index2), addedCandidates[index6]));
                                                }
                                            }             
                                        }
                                    }

                                    if(candidatesToRemove.size() > 0) {
                                        return make_tuple(true, candidatesToStay, candidatesToRemove);
                                    }
                                }

                                for(int index5 = 0; index5 < candidatesToStayCounter3; index5++) {
                                    candidatesToStay.pop_back();
                                }

                                for(int index5 = 0; index5 < candidatesAddedCounter3; index5++) {
                                    addedCandidates.pop_back();
                                }
                            }
                        }

                        for(int index4 = 0; index4 < candidatesToStayCounter2; index4++) {
                            candidatesToStay.pop_back();
                        }

                        for(int index4 = 0; index4 < candidatesAddedCounter2; index4++) {
                            addedCandidates.pop_back();
                        }
                    }
                }

                for(int index3 = 0; index3 < candidatesToStayCounter1; index3++) {
                    candidatesToStay.pop_back();
                }

                for(int index3 = 0; index3 < candidatesAddedCounter1; index3++) {
                    addedCandidates.pop_back();
                }
            }
        }
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedTriplesInBox(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            if(puzzle[index1][index2] == 0) {
                int candidatesBox[3][3][9];
                fill_n(&candidatesBox[0][0][0], sizeof(candidatesBox) / sizeof(***candidatesBox), 0);

                getCandidatesBox(candidates, index1, index2, candidatesBox);

                vector<int> addedCandidates;

                int candidatesToStayCounter1 = 0;
                int candidatesAddedCounter1 = 0;

                for(int index3 = 0; index3 < 9; index3++) {
                    if(candidatesBox[index1 % 3][index2 % 3][index3] == 1) {
                        candidatesToStayCounter1++;

                        candidatesToStay.push_back(make_tuple(make_tuple(index1, index2), index3));

                        bool candidateAdded = false;

                        for(int index4 = 0; index4 < addedCandidates.size(); index4++) {
                            if(addedCandidates[index4] == index3) {
                                candidateAdded = true;
                            }
                        }

                        if(candidateAdded == false) {
                            candidatesAddedCounter1++;

                            addedCandidates.push_back(index3);
                        }
                    }
                }

                if(candidatesToStayCounter1 > 0 && addedCandidates.size() >= 1 && addedCandidates.size() <= 3) {
                    for(int index3 = (index1 % 3) * 3 + index2 % 3 + 1; index3 < 9; index3++) {
                        int candidatesToStayCounter2 = 0;
                        int candidatesAddedCounter2 = 0;

                        for(int index4 = 0; index4 < 9; index4++) {
                            if(candidatesBox[index3 / 3][index3 % 3][index4] == 1) {
                                candidatesToStayCounter2++;

                                candidatesToStay.push_back(make_tuple(make_tuple(index1 - index1 % 3 + index3 / 3, index2 - index2 % 3 + index3 % 3), index4));

                                bool candidateAdded = false;

                                for(int index5 = 0; index5 < addedCandidates.size(); index5++) {
                                    if(addedCandidates[index5] == index4) {
                                        candidateAdded = true;
                                    }
                                }

                                if(candidateAdded == false) {
                                    candidatesAddedCounter2++;

                                    addedCandidates.push_back(index4);
                                }
                            }
                        }

                        if(candidatesToStayCounter2 > 0 && addedCandidates.size() >= 1 && addedCandidates.size() <= 3) {
                            for(int index4 = index3 + 1; index4 < 9; index4++) {
                                int candidatesToStayCounter3 = 0;
                                int candidatesAddedCounter3 = 0;

                                for(int index5 = 0; index5 < 9; index5++) {
                                    if(candidatesBox[index4 / 3][index4 % 3][index5] == 1) {
                                        candidatesToStayCounter3++;

                                        candidatesToStay.push_back(make_tuple(make_tuple(index1 - index1 % 3 + index4 / 3, index2 - index2 % 3 + index4 % 3), index5));

                                        bool candidateAdded = false;

                                        for(int index6 = 0; index6 < addedCandidates.size(); index6++) {
                                            if(addedCandidates[index6] == index5) {
                                                candidateAdded = true;
                                            }
                                        }

                                        if(candidateAdded == false) {
                                            candidatesAddedCounter3++;

                                            addedCandidates.push_back(index5);
                                        }
                                    }
                                }

                                if(candidatesToStayCounter3 > 0 && addedCandidates.size() == 3) {
                                    for(int index5 = 0; index5 < 9; index5++) {
                                        if(index5 != index1 % 3 * 3 + index2 % 3 && index5 != index3 && index5 != index4) {
                                            for(int index6 = 0; index6 < addedCandidates.size(); index6++) {
                                                if(candidatesBox[index5 / 3][index5 % 3][addedCandidates[index6]] == 1) {
                                                    candidatesToRemove.push_back(make_tuple(make_tuple(index1 - index1 % 3 + index5 / 3, index2 - index2 % 3 + index5 % 3), addedCandidates[index6]));
                                                }
                                            }             
                                        }
                                    }

                                    if(candidatesToRemove.size() > 0) {
                                        return make_tuple(true, candidatesToStay, candidatesToRemove);
                                    }
                                }

                                for(int index5 = 0; index5 < candidatesToStayCounter3; index5++) {
                                    candidatesToStay.pop_back();
                                }

                                for(int index5 = 0; index5 < candidatesAddedCounter3; index5++) {
                                    addedCandidates.pop_back();
                                }
                            }
                        }

                        for(int index4 = 0; index4 < candidatesToStayCounter2; index4++) {
                            candidatesToStay.pop_back();
                        }

                        for(int index4 = 0; index4 < candidatesAddedCounter2; index4++) {
                            addedCandidates.pop_back();
                        }
                    }
                }

                for(int index3 = 0; index3 < candidatesToStayCounter1; index3++) {
                    candidatesToStay.pop_back();
                }

                for(int index3 = 0; index3 < candidatesAddedCounter1; index3++) {
                    addedCandidates.pop_back();
                }
            }
        }
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}



tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedQuadsInRow(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            if(puzzle[index1][index2] == 0) {
                int candidatesRow[9][9];
                fill_n(&candidatesRow[0][0], sizeof(candidatesRow) / sizeof(**candidatesRow), 0);

                getCandidatesRow(candidates, index1, candidatesRow);

                vector<int> addedCandidates;

                int candidatesToStayCounter1 = 0;
                int candidatesAddedCounter1 = 0;

                for(int index3 = 0; index3 < 9; index3++) {
                    if(candidatesRow[index2][index3] == 1) {
                        candidatesToStayCounter1++;

                        candidatesToStay.push_back(make_tuple(make_tuple(index1, index2), index3));

                        bool candidateAdded = false;

                        for(int index4 = 0; index4 < addedCandidates.size(); index4++) {
                            if(addedCandidates[index4] == index3) {
                                candidateAdded = true;
                            }
                        }

                        if(candidateAdded == false) {
                            candidatesAddedCounter1++;

                            addedCandidates.push_back(index3);
                        }
                    }
                }

                if(candidatesToStayCounter1 > 0 && addedCandidates.size() >= 1 && addedCandidates.size() <= 4) {
                    for(int index3 = index2 + 1; index3 < 9; index3++) {
                        int candidatesToStayCounter2 = 0;
                        int candidatesAddedCounter2 = 0;

                        for(int index4 = 0; index4 < 9; index4++) {
                            if(candidatesRow[index3][index4] == 1) {
                                candidatesToStayCounter2++;

                                candidatesToStay.push_back(make_tuple(make_tuple(index1, index3), index4));

                                bool candidateAdded = false;

                                for(int index5 = 0; index5 < addedCandidates.size(); index5++) {
                                    if(addedCandidates[index5] == index4) {
                                        candidateAdded = true;
                                    }
                                }

                                if(candidateAdded == false) {
                                    candidatesAddedCounter2++;

                                    addedCandidates.push_back(index4);
                                }
                            }
                        }

                        if(candidatesToStayCounter2 > 0 && addedCandidates.size() >= 1 && addedCandidates.size() <= 4) {
                            for(int index4 = index3 + 1; index4 < 9; index4++) {
                                int candidatesToStayCounter3 = 0;
                                int candidatesAddedCounter3 = 0;

                                for(int index5 = 0; index5 < 9; index5++) {
                                    if(candidatesRow[index4][index5] == 1) {
                                        candidatesToStayCounter3++;

                                        candidatesToStay.push_back(make_tuple(make_tuple(index1, index4), index5));

                                        bool candidateAdded = false;

                                        for(int index6 = 0; index6 < addedCandidates.size(); index6++) {
                                            if(addedCandidates[index6] == index5) {
                                                candidateAdded = true;
                                            }
                                        }

                                        if(candidateAdded == false) {
                                            candidatesAddedCounter3++;

                                            addedCandidates.push_back(index5);
                                        }
                                    }
                                }

                                if(candidatesToStayCounter3 > 0 && addedCandidates.size() >= 1 && addedCandidates.size() <= 4) {
                                    for(int index5 = index4 + 1; index5 < 9; index5++) {
                                        int candidatesToStayCounter4 = 0;
                                        int candidatesAddedCounter4 = 0;

                                        for(int index6 = 0; index6 < 9; index6++) {
                                            if(candidatesRow[index5][index6] == 1) {
                                                candidatesToStayCounter4++;

                                                candidatesToStay.push_back(make_tuple(make_tuple(index1, index5), index6));

                                                bool candidateAdded = false;

                                                for(int index7 = 0; index7 < addedCandidates.size(); index7++) {
                                                    if(addedCandidates[index7] == index6) {
                                                        candidateAdded = true;
                                                    }
                                                }

                                                if(candidateAdded == false) {
                                                    candidatesAddedCounter4++;
                                                    addedCandidates.push_back(index6);
                                                }
                                            }
                                        }

                                        if(candidatesToStayCounter4 > 0 && addedCandidates.size() == 4) {
                                            for(int index6 = 0; index6 < 9; index6++) {
                                                if(index6 != index2 && index6 != index3 && index6 != index4 && index6 != index5) {
                                                    for(int index7 = 0; index7 < addedCandidates.size(); index7++) {
                                                        if(candidatesRow[index6][addedCandidates[index7]] == 1) {
                                                            candidatesToRemove.push_back(make_tuple(make_tuple(index1, index6), addedCandidates[index7]));
                                                        }
                                                    }             
                                                }
                                            }

                                            if(candidatesToRemove.size() > 0) {
                                                return make_tuple(true, candidatesToStay, candidatesToRemove);
                                            }
                                        }

                                        for(int index6 = 0; index6 < candidatesToStayCounter4; index6++) {
                                            candidatesToStay.pop_back();
                                        }

                                        for(int index6 = 0; index6 < candidatesAddedCounter4; index6++) {
                                            addedCandidates.pop_back();
                                        }
                                    }
                                }

                                for(int index5 = 0; index5 < candidatesToStayCounter3; index5++) {
                                    candidatesToStay.pop_back();
                                }

                                for(int index5 = 0; index5 < candidatesAddedCounter3; index5++) {
                                    addedCandidates.pop_back();
                                }
                            }
                        }

                        for(int index4 = 0; index4 < candidatesToStayCounter2; index4++) {
                            candidatesToStay.pop_back();
                        }

                        for(int index4 = 0; index4 < candidatesAddedCounter2; index4++) {
                            addedCandidates.pop_back();
                        }
                    }
                }

                for(int index3 = 0; index3 < candidatesToStayCounter1; index3++) {
                    candidatesToStay.pop_back();
                }

                for(int index3 = 0; index3 < candidatesAddedCounter1; index3++) {
                    addedCandidates.pop_back();
                }
            }
        }
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedQuadsInColumn(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            if(puzzle[index1][index2] == 0) {
                int candidatesColumn[9][9];
                fill_n(&candidatesColumn[0][0], sizeof(candidatesColumn) / sizeof(**candidatesColumn), 0);

                getCandidatesColumn(candidates, index2, candidatesColumn);

                vector<int> addedCandidates;

                int candidatesToStayCounter1 = 0;
                int candidatesAddedCounter1 = 0;

                for(int index3 = 0; index3 < 9; index3++) {
                    if(candidatesColumn[index1][index3] == 1) {
                        candidatesToStayCounter1++;

                        candidatesToStay.push_back(make_tuple(make_tuple(index1, index2), index3));

                        bool candidateAdded = false;

                        for(int index4 = 0; index4 < addedCandidates.size(); index4++) {
                            if(addedCandidates[index4] == index3) {
                                candidateAdded = true;
                            }
                        }

                        if(candidateAdded == false) {
                            candidatesAddedCounter1++;

                            addedCandidates.push_back(index3);
                        }
                    }
                }

                if(candidatesToStayCounter1 > 0 && addedCandidates.size() >= 1 && addedCandidates.size() <= 4) {
                    for(int index3 = index1 + 1; index3 < 9; index3++) {
                        int candidatesToStayCounter2 = 0;
                        int candidatesAddedCounter2 = 0;

                        for(int index4 = 0; index4 < 9; index4++) {
                            if(candidatesColumn[index3][index4] == 1) {
                                candidatesToStayCounter2++;

                                candidatesToStay.push_back(make_tuple(make_tuple(index3, index2), index4));

                                bool candidateAdded = false;

                                for(int index5 = 0; index5 < addedCandidates.size(); index5++) {
                                    if(addedCandidates[index5] == index4) {
                                        candidateAdded = true;
                                    }
                                }

                                if(candidateAdded == false) {
                                    candidatesAddedCounter2++;

                                    addedCandidates.push_back(index4);
                                }
                            }
                        }

                        if(candidatesToStayCounter2 > 0 && addedCandidates.size() >= 1 && addedCandidates.size() <= 4) {
                            for(int index4 = index3 + 1; index4 < 9; index4++) {
                                int candidatesToStayCounter3 = 0;
                                int candidatesAddedCounter3 = 0;

                                for(int index5 = 0; index5 < 9; index5++) {
                                    if(candidatesColumn[index4][index5] == 1) {
                                        candidatesToStayCounter3++;

                                        candidatesToStay.push_back(make_tuple(make_tuple(index4, index2), index5));

                                        bool candidateAdded = false;

                                        for(int index6 = 0; index6 < addedCandidates.size(); index6++) {
                                            if(addedCandidates[index6] == index5) {
                                                candidateAdded = true;
                                            }
                                        }

                                        if(candidateAdded == false) {
                                            candidatesAddedCounter3++;

                                            addedCandidates.push_back(index5);
                                        }
                                    }
                                }

                                if(candidatesToStayCounter3 > 0 && addedCandidates.size() >= 1 && addedCandidates.size() <= 4) {
                                    for(int index5 = index4 + 1; index5 < 9; index5++) {
                                        int candidatesToStayCounter4 = 0;
                                        int candidatesAddedCounter4 = 0;

                                        for(int index6 = 0; index6 < 9; index6++) {
                                            if(candidatesColumn[index5][index6] == 1) {
                                                candidatesToStayCounter4++;

                                                candidatesToStay.push_back(make_tuple(make_tuple(index5, index2), index6));

                                                bool candidateAdded = false;

                                                for(int index7 = 0; index7 < addedCandidates.size(); index7++) {
                                                    if(addedCandidates[index7] == index6) {
                                                        candidateAdded = true;
                                                    }
                                                }

                                                if(candidateAdded == false) {
                                                    candidatesAddedCounter4++;

                                                    addedCandidates.push_back(index6);
                                                }
                                            }
                                        }

                                        if(candidatesToStayCounter4 > 0 && addedCandidates.size() == 4) {
                                            for(int index6 = 0; index6 < 9; index6++) {
                                                if(index6 != index1 && index6 != index3 && index6 != index4 && index6 != index5) {
                                                    for(int index7 = 0; index7 < addedCandidates.size(); index7++) {
                                                        if(candidatesColumn[index6][addedCandidates[index7]] == 1) {
                                                            candidatesToRemove.push_back(make_tuple(make_tuple(index6, index2), addedCandidates[index7]));
                                                        }
                                                    }             
                                                }
                                            }

                                            if(candidatesToRemove.size() > 0) {
                                                return make_tuple(true, candidatesToStay, candidatesToRemove);
                                            }
                                        }

                                        for(int index6 = 0; index6 < candidatesToStayCounter4; index6++) {
                                            candidatesToStay.pop_back();
                                        }

                                        for(int index6 = 0; index6 < candidatesAddedCounter4; index6++) {
                                            addedCandidates.pop_back();
                                        }
                                    }
                                }

                                for(int index5 = 0; index5 < candidatesToStayCounter3; index5++) {
                                    candidatesToStay.pop_back();
                                }

                                for(int index5 = 0; index5 < candidatesAddedCounter3; index5++) {
                                    addedCandidates.pop_back();
                                }
                            }
                        }

                        for(int index4 = 0; index4 < candidatesToStayCounter2; index4++) {
                            candidatesToStay.pop_back();
                        }

                        for(int index4 = 0; index4 < candidatesAddedCounter2; index4++) {
                            addedCandidates.pop_back();
                        }
                    }
                }

                for(int index3 = 0; index3 < candidatesToStayCounter1; index3++) {
                    candidatesToStay.pop_back();
                }

                for(int index3 = 0; index3 < candidatesAddedCounter1; index3++) {
                    addedCandidates.pop_back();
                }
            }
        }
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> nakedQuadsInBox(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1++) {
        for(int index2 = 0; index2 < 9; index2++) {
            if(puzzle[index1][index2] == 0) {
                int candidatesBox[3][3][9];
                fill_n(&candidatesBox[0][0][0], sizeof(candidatesBox) / sizeof(***candidatesBox), 0);

                getCandidatesBox(candidates, index1, index2, candidatesBox);

                vector<int> addedCandidates;

                int candidatesToStayCounter1 = 0;
                int candidatesAddedCounter1 = 0;

                for(int index3 = 0; index3 < 9; index3++) {
                    if(candidatesBox[index1 % 3][index2 % 3][index3] == 1) {
                        candidatesToStayCounter1++;

                        candidatesToStay.push_back(make_tuple(make_tuple(index1, index2), index3));

                        bool candidateAdded = false;

                        for(int index4 = 0; index4 < addedCandidates.size(); index4++) {
                            if(addedCandidates[index4] == index3) {
                                candidateAdded = true;
                            }
                        }

                        if(candidateAdded == false) {
                            candidatesAddedCounter1++;

                            addedCandidates.push_back(index3);
                        }
                    }
                }

                if(candidatesToStayCounter1 > 0 && addedCandidates.size() >= 1 && addedCandidates.size() <= 4) {
                    for(int index3 = (index1 % 3) * 3 + index2 % 3 + 1; index3 < 9; index3++) {
                        int candidatesToStayCounter2 = 0;
                        int candidatesAddedCounter2 = 0;

                        for(int index4 = 0; index4 < 9; index4++) {
                            if(candidatesBox[index3 / 3][index3 % 3][index4] == 1) {
                                candidatesToStayCounter2++;

                                candidatesToStay.push_back(make_tuple(make_tuple(index1 - index1 % 3 + index3 / 3, index2 - index2 % 3 + index3 % 3), index4));

                                bool candidateAdded = false;

                                for(int index5 = 0; index5 < addedCandidates.size(); index5++) {
                                    if(addedCandidates[index5] == index4) {
                                        candidateAdded = true;
                                    }
                                }

                                if(candidateAdded == false) {
                                    candidatesAddedCounter2++;

                                    addedCandidates.push_back(index4);
                                }
                            }
                        }

                        if(candidatesToStayCounter2 > 0 && addedCandidates.size() >= 1 && addedCandidates.size() <= 4) {
                            for(int index4 = index3 + 1; index4 < 9; index4++) {
                                int candidatesToStayCounter3 = 0;
                                int candidatesAddedCounter3 = 0;

                                for(int index5 = 0; index5 < 9; index5++) {
                                    if(candidatesBox[index4 / 3][index4 % 3][index5] == 1) {
                                        candidatesToStayCounter3++;

                                        candidatesToStay.push_back(make_tuple(make_tuple(index1 - index1 % 3 + index4 / 3, index2 - index2 % 3 + index4 % 3), index5));

                                        bool candidateAdded = false;

                                        for(int index6 = 0; index6 < addedCandidates.size(); index6++) {
                                            if(addedCandidates[index6] == index5) {
                                                candidateAdded = true;
                                            }
                                        }

                                        if(candidateAdded == false) {
                                            candidatesAddedCounter3++;

                                            addedCandidates.push_back(index5);
                                        }
                                    }
                                }

                                if(candidatesToStayCounter3 > 0 && addedCandidates.size() >= 1 && addedCandidates.size() <= 4) {
                                    for(int index5 = index4 + 1; index5 < 9; index5++){
                                        int candidatesToStayCounter4 = 0;
                                        int candidatesAddedCounter4 = 0;

                                        for(int index6 = 0; index6 < 9; index6++) {
                                            if(candidatesBox[index5 / 3][index5 % 3][index6] == 1) {
                                                candidatesToStayCounter4++;

                                                candidatesToStay.push_back(make_tuple(make_tuple(index1 - index1 % 3 + index5 / 3, index2 - index2 % 3 + index5 % 3), index6));

                                                bool candidateAdded = false;

                                                for(int index7 = 0; index7 < addedCandidates.size(); index7++) {
                                                    if(addedCandidates[index7] == index6) {
                                                        candidateAdded = true;
                                                    }
                                                }

                                                if(candidateAdded == false) {
                                                    candidatesAddedCounter4++;

                                                    addedCandidates.push_back(index6);
                                                }
                                            }
                                        }

                                        if(candidatesToStayCounter4 > 0 && addedCandidates.size() == 4) {
                                            for(int index6 = 0; index6 < 9; index6++) {
                                                if(index6 != index1 % 3 * 3 + index2 % 3 && index6 != index3 && index6 != index4 && index6 != index5) {
                                                    for(int index7 = 0; index7 < addedCandidates.size(); index7++) {
                                                        if(candidatesBox[index6 / 3][index6 % 3][addedCandidates[index7]] == 1) {
                                                            candidatesToRemove.push_back(make_tuple(make_tuple(index1 - index1 % 3 + index6 / 3, index2 - index2 % 3 + index6 % 3), addedCandidates[index7]));
                                                        }
                                                    }             
                                                }
                                            }

                                            if(candidatesToRemove.size() > 0) {
                                                return make_tuple(true, candidatesToStay, candidatesToRemove);
                                            }
                                        }

                                        for(int index6 = 0; index6 < candidatesToStayCounter4; index6++) {
                                            candidatesToStay.pop_back();
                                        }

                                        for(int index6 = 0; index6 < candidatesAddedCounter4; index6++) {
                                            addedCandidates.pop_back();
                                        }
                                    }
                                }

                                for(int index5 = 0; index5 < candidatesToStayCounter3; index5++) {
                                    candidatesToStay.pop_back();
                                }

                                for(int index5 = 0; index5 < candidatesAddedCounter3; index5++) {
                                    addedCandidates.pop_back();
                                }
                            }
                        }

                        for(int index4 = 0; index4 < candidatesToStayCounter2; index4++) {
                            candidatesToStay.pop_back();
                        }

                        for(int index4 = 0; index4 < candidatesAddedCounter2; index4++) {
                            addedCandidates.pop_back();
                        }
                    }
                }

                for(int index3 = 0; index3 < candidatesToStayCounter1; index3++) {
                    candidatesToStay.pop_back();
                }

                for(int index3 = 0; index3 < candidatesAddedCounter1; index3++) {
                    addedCandidates.pop_back();
                }
            }
        }
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}



tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenPairsInRow(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1++) {
        int candidatesRow[9][9];
        fill_n(&candidatesRow[0][0], sizeof(candidatesRow) / sizeof(**candidatesRow), 0);

        getCandidatesRow(candidates, index1, candidatesRow);

        int candidatesShowupCounter[9];

        fill_n(&candidatesShowupCounter[0], sizeof(candidatesShowupCounter) / sizeof(*candidatesShowupCounter), 0);

        for(int index2 = 0; index2 < 9; index2++) {
            for(int index3 = 0; index3 < 9; index3++) {
                if(candidatesRow[index2][index3] == 1) {
                    candidatesShowupCounter[index3]++;
                }
            }
        }

        vector<int> addedCandidates;
        vector<int> removedCandidates;

        for(int index2 = 0; index2 < 9; index2++) {
            if(candidatesShowupCounter[index2] == 2) {
                addedCandidates.push_back(index2);
            }
            else {
                removedCandidates.push_back(index2);
            }
        }

        if(addedCandidates.size() == 2) {
            vector<int> addedCells;

            for(int index2 = 0; index2 < 9; index2++) {
                int candidateConfirmationCounter = 0;

                for(int index3 = 0; index3 < addedCandidates.size(); index3++) {
                    if(candidatesRow[index2][addedCandidates[index3]] == 1) {
                        candidateConfirmationCounter++;
                    }
                }

                if(candidateConfirmationCounter == 2) {
                    addedCells.push_back(index2);
                }
            }

            if(addedCells.size() == 2) {
                for(int index2 = 0; index2 < addedCells.size(); index2++) {
                    for(int index3 = 0; index3 < addedCandidates.size(); index3++) {
                        if(candidatesRow[addedCells[index2]][addedCandidates[index3]] == 1) {
                            candidatesToStay.push_back(make_tuple(make_tuple(index1, addedCells[index2]), addedCandidates[index3]));
                        }
                    }

                    for(int index3 = 0; index3 < removedCandidates.size(); index3++) {
                        if(candidatesRow[addedCells[index2]][removedCandidates[index3]] == 1) {
                            candidatesToRemove.push_back(make_tuple(make_tuple(index1, addedCells[index2]), removedCandidates[index3]));
                        }
                    }
                }

                if(candidatesToRemove.size() > 0) {
                    return make_tuple(true, candidatesToStay, candidatesToRemove);
                }

                candidatesToStay.clear();
            }

            addedCells.clear();
        }

        addedCandidates.clear();
        removedCandidates.clear();
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenPairsInColumn(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1++) {
        int candidatesColumn[9][9];
        fill_n(&candidatesColumn[0][0], sizeof(candidatesColumn) / sizeof(**candidatesColumn), 0);

        getCandidatesColumn(candidates, index1, candidatesColumn);

        int candidatesShowupCounter[9];

        fill_n(&candidatesShowupCounter[0], sizeof(candidatesShowupCounter) / sizeof(*candidatesShowupCounter), 0);

        for(int index2 = 0; index2 < 9; index2++) {
            for(int index3 = 0; index3 < 9; index3++) {
                if(candidatesColumn[index2][index3] == 1) {
                    candidatesShowupCounter[index3]++;
                }
            }
        }

        vector<int> addedCandidates;
        vector<int> removedCandidates;

        for(int index2 = 0; index2 < 9; index2++) {
            if(candidatesShowupCounter[index2] == 2) {
                addedCandidates.push_back(index2);
            }
            else {
                removedCandidates.push_back(index2);
            }
        }

        if(addedCandidates.size() == 2) {
            vector<int> addedCells;

            for(int index2 = 0; index2 < 9; index2++) {
                int candidateConfirmationCounter = 0;

                for(int index3 = 0; index3 < addedCandidates.size(); index3++) {
                    if(candidatesColumn[index2][addedCandidates[index3]] == 1) {
                        candidateConfirmationCounter++;
                    }
                }

                if(candidateConfirmationCounter == 2) {
                    addedCells.push_back(index2);
                }
            }

            if(addedCells.size() == 2) {
                for(int index2 = 0; index2 < addedCells.size(); index2++) {
                    for(int index3 = 0; index3 < addedCandidates.size(); index3++) {
                        if(candidatesColumn[addedCells[index2]][addedCandidates[index3]] == 1) {
                            candidatesToStay.push_back(make_tuple(make_tuple(index1, addedCells[index2]), addedCandidates[index3]));
                        }
                    }

                    for(int index3 = 0; index3 < removedCandidates.size(); index3++) {
                        if(candidatesColumn[addedCells[index2]][removedCandidates[index3]] == 1) {
                            candidatesToRemove.push_back(make_tuple(make_tuple(index1, addedCells[index2]), removedCandidates[index3]));
                        }
                    }
                }

                if(candidatesToRemove.size() > 0) {
                    return make_tuple(true, candidatesToStay, candidatesToRemove);
                }

                candidatesToStay.clear();
            }

            addedCells.clear();
        }

        addedCandidates.clear();
        removedCandidates.clear();
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenPairsInBox(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1 = index1 + 3) {
        for(int index2 = 0; index2 < 9; index2 = index2 + 3) {
            int candidatesBox[3][3][9];
            fill_n(&candidatesBox[0][0][0], sizeof(candidatesBox) / sizeof(***candidatesBox), 0);

            getCandidatesBox(candidates, index1, index2, candidatesBox);

            int candidatesShowupCounter[9];

            fill_n(&candidatesShowupCounter[0], sizeof(candidatesShowupCounter) / sizeof(*candidatesShowupCounter), 0);

            for(int index3 = 0; index3 < 9; index3++) {
                for(int index4 = 0; index4 < 9; index4++) {
                    if(candidatesBox[index3 / 3][index3 % 3][index4] == 1) {
                        candidatesShowupCounter[index4]++;
                    }
                }
            }

            vector<int> addedCandidates;
            vector<int> removedCandidates;

            for(int index3 = 0; index3 < 9; index3++) {
                if(candidatesShowupCounter[index3] == 2) {
                    addedCandidates.push_back(index3);
                }
                else {
                    removedCandidates.push_back(index3);
                }
            }

            if(addedCandidates.size() == 2) {
                vector<int> addedCells;

                for(int index3 = 0; index3 < 9; index3++) {
                    int candidateConfirmationCounter = 0;

                    for(int index4 = 0; index4 < addedCandidates.size(); index4++) {
                        if(candidatesBox[index3 / 3][index3 % 3][addedCandidates[index4]] == 1) {
                            candidateConfirmationCounter++;
                        }
                    }

                    if(candidateConfirmationCounter == 2) {
                        addedCells.push_back(index3);
                    }
                }

                if(addedCells.size() == 2) {
                    for(int index3 = 0; index3 < addedCells.size(); index3++) {
                        for(int index4 = 0; index4 < addedCandidates.size(); index4++) {
                            if(candidatesBox[addedCells[index3] / 3][addedCells[index3] % 3][addedCandidates[index4]] == 1) {
                                candidatesToStay.push_back(make_tuple(make_tuple(index1, addedCells[index3]), addedCandidates[index4]));
                            }
                        }

                        for(int index4 = 0; index4 < removedCandidates.size(); index4++) {
                            if(candidatesBox[addedCells[index3] / 3][addedCells[index3] % 3][removedCandidates[index4]] == 1) {
                                candidatesToRemove.push_back(make_tuple(make_tuple(index1, addedCells[index3]), removedCandidates[index4]));
                            }
                        }
                    }

                    if(candidatesToRemove.size() > 0) {
                        return make_tuple(true, candidatesToStay, candidatesToRemove);
                    }

                    candidatesToStay.clear();
                }

                addedCells.clear();
            }

            addedCandidates.clear();
            removedCandidates.clear();
        }
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}



tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenTriplesInRow(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1++) {
        int candidatesRow[9][9];
        fill_n(&candidatesRow[0][0], sizeof(candidatesRow) / sizeof(**candidatesRow), 0);

        getCandidatesRow(candidates, index1, candidatesRow);

        int candidatesShowupCounter[9];

        fill_n(&candidatesShowupCounter[0], sizeof(candidatesShowupCounter) / sizeof(*candidatesShowupCounter), 0);

        for(int index2 = 0; index2 < 9; index2++) {
            for(int index3 = 0; index3 < 9; index3++) {
                if(candidatesRow[index2][index3] == 1) {
                    candidatesShowupCounter[index3]++;
                }
            }
        }

        vector<int> addedCandidates;
        vector<int> removedCandidates;

        for(int index2 = 0; index2 < 9; index2++) {
            if(candidatesShowupCounter[index2] >= 1 && candidatesShowupCounter[index2] <= 3) {
                addedCandidates.push_back(index2);
            }
            else {
                removedCandidates.push_back(index2);
            }
        }

        if(addedCandidates.size() == 3) {
            vector<int> addedCells;

            for(int index2 = 0; index2 < 9; index2++) {
                int candidateConfirmationCounter = 0;

                for(int index3 = 0; index3 < addedCandidates.size(); index3++) {
                    if(candidatesRow[index2][addedCandidates[index3]] == 1) {
                        candidateConfirmationCounter++;
                    }
                }

                if(candidateConfirmationCounter >= 1) {
                    addedCells.push_back(index2);
                }
            }

            if(addedCells.size() == 3) {
                for(int index2 = 0; index2 < addedCells.size(); index2++) {
                    for(int index3 = 0; index3 < addedCandidates.size(); index3++) {
                        if(candidatesRow[addedCells[index2]][addedCandidates[index3]] == 1) {
                            candidatesToStay.push_back(make_tuple(make_tuple(index1, addedCells[index2]), addedCandidates[index3]));
                        }
                    }

                    for(int index3 = 0; index3 < removedCandidates.size(); index3++) {
                        if(candidatesRow[addedCells[index2]][removedCandidates[index3]] == 1) {
                            candidatesToRemove.push_back(make_tuple(make_tuple(index1, addedCells[index2]), removedCandidates[index3]));
                        }
                    }
                }

                if(candidatesToRemove.size() > 0) {
                    return make_tuple(true, candidatesToStay, candidatesToRemove);
                }

                candidatesToStay.clear();
            }

            addedCells.clear();
        }

        addedCandidates.clear();
        removedCandidates.clear();
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenTriplesInColumn(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1++) {
        int candidatesColumn[9][9];
        fill_n(&candidatesColumn[0][0], sizeof(candidatesColumn) / sizeof(**candidatesColumn), 0);

        getCandidatesColumn(candidates, index1, candidatesColumn);

        int candidatesShowupCounter[9];

        fill_n(&candidatesShowupCounter[0], sizeof(candidatesShowupCounter) / sizeof(*candidatesShowupCounter), 0);

        for(int index2 = 0; index2 < 9; index2++) {
            for(int index3 = 0; index3 < 9; index3++) {
                if(candidatesColumn[index2][index3] == 1) {
                    candidatesShowupCounter[index3]++;
                }
            }
        }

        vector<int> addedCandidates;
        vector<int> removedCandidates;

        for(int index2 = 0; index2 < 9; index2++) {
            if(candidatesShowupCounter[index2] >= 1 && candidatesShowupCounter[index2] <= 3) {
                addedCandidates.push_back(index2);
            }
            else {
                removedCandidates.push_back(index2);
            }
        }

        if(addedCandidates.size() == 3) {
            vector<int> addedCells;

            for(int index2 = 0; index2 < 9; index2++) {
                int candidateConfirmationCounter = 0;

                for(int index3 = 0; index3 < addedCandidates.size(); index3++) {
                    if(candidatesColumn[index2][addedCandidates[index3]] == 1) {
                        candidateConfirmationCounter++;
                    }
                }

                if(candidateConfirmationCounter >= 1) {
                    addedCells.push_back(index2);
                }
            }

            if(addedCells.size() == 3) {
                for(int index2 = 0; index2 < addedCells.size(); index2++) {
                    for(int index3 = 0; index3 < addedCandidates.size(); index3++) {
                        if(candidatesColumn[addedCells[index2]][addedCandidates[index3]] == 1) {
                            candidatesToStay.push_back(make_tuple(make_tuple(index1, addedCells[index2]), addedCandidates[index3]));
                        }
                    }

                    for(int index3 = 0; index3 < removedCandidates.size(); index3++) {
                        if(candidatesColumn[addedCells[index2]][removedCandidates[index3]] == 1) {
                            candidatesToRemove.push_back(make_tuple(make_tuple(index1, addedCells[index2]), removedCandidates[index3]));
                        }
                    }
                }

                if(candidatesToRemove.size() > 0) {
                    return make_tuple(true, candidatesToStay, candidatesToRemove);
                }

                candidatesToStay.clear();
            }

            addedCells.clear();
        }

        addedCandidates.clear();
        removedCandidates.clear();
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove); 
}

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenTriplesInBox(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1 = index1 + 3) {
        for(int index2 = 0; index2 < 9; index2 = index2 + 3) {
            int candidatesBox[3][3][9];
            fill_n(&candidatesBox[0][0][0], sizeof(candidatesBox) / sizeof(***candidatesBox), 0);

            getCandidatesBox(candidates, index1, index2, candidatesBox);

            int candidatesShowupCounter[9];

            fill_n(&candidatesShowupCounter[0], sizeof(candidatesShowupCounter) / sizeof(*candidatesShowupCounter), 0);

            for(int index3 = 0; index3 < 9; index3++) {
                for(int index4 = 0; index4 < 9; index4++) {
                    if(candidatesBox[index3 / 3][index3 % 3][index4] == 1) {
                        candidatesShowupCounter[index4]++;
                    }
                }
            }

            vector<int> addedCandidates;
            vector<int> removedCandidates;

            for(int index3 = 0; index3 < 9; index3++) {
                if(candidatesShowupCounter[index3] >= 1 && candidatesShowupCounter[index3] <= 3) {
                    addedCandidates.push_back(index3);
                }
                else {
                    removedCandidates.push_back(index3);
                }
            }

            if(addedCandidates.size() == 3) {
                vector<int> addedCells;

                for(int index3 = 0; index3 < 9; index3++) {
                    int candidateConfirmationCounter = 0;

                    for(int index4 = 0; index4 < addedCandidates.size(); index4++) {
                        if(candidatesBox[index3 / 3][index3 % 3][addedCandidates[index4]] == 1) {
                            candidateConfirmationCounter++;
                        }
                    }

                    if(candidateConfirmationCounter >= 1) {
                        addedCells.push_back(index3);
                    }
                }

                if(addedCells.size() == 3) {
                    for(int index3 = 0; index3 < addedCells.size(); index3++) {
                        for(int index4 = 0; index4 < addedCandidates.size(); index4++) {
                            if(candidatesBox[addedCells[index3] / 3][addedCells[index3] % 3][addedCandidates[index4]] == 1) {
                                candidatesToStay.push_back(make_tuple(make_tuple(index1, addedCells[index3]), addedCandidates[index4]));
                            }
                        }

                        for(int index4 = 0; index4 < removedCandidates.size(); index4++) {
                            if(candidatesBox[addedCells[index3] / 3][addedCells[index3] % 3][removedCandidates[index4]] == 1) {
                                candidatesToRemove.push_back(make_tuple(make_tuple(index1, addedCells[index3]), removedCandidates[index4]));
                            }
                        }
                    }

                    if(candidatesToRemove.size() > 0) {
                        return make_tuple(true, candidatesToStay, candidatesToRemove);
                    }

                    candidatesToStay.clear();
                }

                addedCells.clear();
            }

            addedCandidates.clear();
            removedCandidates.clear();
        }
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}



tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenQuadsInRow(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1++) {
        int candidatesRow[9][9];
        fill_n(&candidatesRow[0][0], sizeof(candidatesRow) / sizeof(**candidatesRow), 0);

        getCandidatesRow(candidates, index1, candidatesRow);

        int candidatesShowupCounter[9];

        fill_n(&candidatesShowupCounter[0], sizeof(candidatesShowupCounter) / sizeof(*candidatesShowupCounter), 0);

        for(int index2 = 0; index2 < 9; index2++) {
            for(int index3 = 0; index3 < 9; index3++) {
                if(candidatesRow[index2][index3] == 1) {
                    candidatesShowupCounter[index3]++;
                }
            }
        }

        vector<int> addedCandidates;
        vector<int> removedCandidates;

        for(int index2 = 0; index2 < 9; index2++) {
            if(candidatesShowupCounter[index2] >= 1 && candidatesShowupCounter[index2] <= 4) {
                addedCandidates.push_back(index2);
            }
            else {
                removedCandidates.push_back(index2);
            }
        }

        if(addedCandidates.size() == 4) {
            vector<int> addedCells;

            for(int index2 = 0; index2 < 9; index2++) {
                int candidateConfirmationCounter = 0;

                for(int index3 = 0; index3 < addedCandidates.size(); index3++) {
                    if(candidatesRow[index2][addedCandidates[index3]] == 1) {
                        candidateConfirmationCounter++;
                    }
                }

                if(candidateConfirmationCounter >= 1) {
                    addedCells.push_back(index2);
                }
            }

            if(addedCells.size() == 4) {
                for(int index2 = 0; index2 < addedCells.size(); index2++) {
                    for(int index3 = 0; index3 < addedCandidates.size(); index3++) {
                        if(candidatesRow[addedCells[index2]][addedCandidates[index3]] == 1) {
                            candidatesToStay.push_back(make_tuple(make_tuple(index1, addedCells[index2]), addedCandidates[index3]));
                        }
                    }

                    for(int index3 = 0; index3 < removedCandidates.size(); index3++) {
                        if(candidatesRow[addedCells[index2]][removedCandidates[index3]] == 1) {
                            candidatesToRemove.push_back(make_tuple(make_tuple(index1, addedCells[index2]), removedCandidates[index3]));
                        }
                    }
                }

                if(candidatesToRemove.size() > 0) {
                    return make_tuple(true, candidatesToStay, candidatesToRemove);
                }

                candidatesToStay.clear();
            }

            addedCells.clear();
        }

        addedCandidates.clear();
        removedCandidates.clear();
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenQuadsInColumn(int puzzle[9][9], int candidates[9][9][9]) {
vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1++) {
        int candidatesColumn[9][9];
        fill_n(&candidatesColumn[0][0], sizeof(candidatesColumn) / sizeof(**candidatesColumn), 0);

        getCandidatesColumn(candidates, index1, candidatesColumn);

        int candidatesShowupCounter[9];

        fill_n(&candidatesShowupCounter[0], sizeof(candidatesShowupCounter) / sizeof(*candidatesShowupCounter), 0);

        for(int index2 = 0; index2 < 9; index2++) {
            for(int index3 = 0; index3 < 9; index3++) {
                if(candidatesColumn[index2][index3] == 1) {
                    candidatesShowupCounter[index3]++;
                }
            }
        }

        vector<int> addedCandidates;
        vector<int> removedCandidates;

        for(int index2 = 0; index2 < 9; index2++) {
            if(candidatesShowupCounter[index2] >= 1 && candidatesShowupCounter[index2] <= 4) {
                addedCandidates.push_back(index2);
            }
            else {
                removedCandidates.push_back(index2);
            }
        }

        if(addedCandidates.size() == 4) {
            vector<int> addedCells;

            for(int index2 = 0; index2 < 9; index2++) {
                int candidateConfirmationCounter = 0;

                for(int index3 = 0; index3 < addedCandidates.size(); index3++) {
                    if(candidatesColumn[index2][addedCandidates[index3]] == 1) {
                        candidateConfirmationCounter++;
                    }
                }

                if(candidateConfirmationCounter >= 1) {
                    addedCells.push_back(index2);
                }
            }

            if(addedCells.size() == 4) {
                for(int index2 = 0; index2 < addedCells.size(); index2++) {
                    for(int index3 = 0; index3 < addedCandidates.size(); index3++) {
                        if(candidatesColumn[addedCells[index2]][addedCandidates[index3]] == 1) {
                            candidatesToStay.push_back(make_tuple(make_tuple(index1, addedCells[index2]), addedCandidates[index3]));
                        }
                    }

                    for(int index3 = 0; index3 < removedCandidates.size(); index3++) {
                        if(candidatesColumn[addedCells[index2]][removedCandidates[index3]] == 1) {
                            candidatesToRemove.push_back(make_tuple(make_tuple(index1, addedCells[index2]), removedCandidates[index3]));
                        }
                    }
                }

                if(candidatesToRemove.size() > 0) {
                    return make_tuple(true, candidatesToStay, candidatesToRemove);
                }

                candidatesToStay.clear();
            }

            addedCells.clear();
        }

        addedCandidates.clear();
        removedCandidates.clear();
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove); 
}

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> hiddenQuadsInBox(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1 = index1 + 3) {
        for(int index2 = 0; index2 < 9; index2 = index2 + 3) {
            int candidatesBox[3][3][9];
            fill_n(&candidatesBox[0][0][0], sizeof(candidatesBox) / sizeof(***candidatesBox), 0);

            getCandidatesBox(candidates, index1, index2, candidatesBox);

            int candidatesShowupCounter[9];

            fill_n(&candidatesShowupCounter[0], sizeof(candidatesShowupCounter) / sizeof(*candidatesShowupCounter), 0);

            for(int index3 = 0; index3 < 9; index3++) {
                for(int index4 = 0; index4 < 9; index4++) {
                    if(candidatesBox[index3 / 3][index3 % 3][index4] == 1) {
                        candidatesShowupCounter[index4]++;
                    }
                }
            }

            vector<int> addedCandidates;
            vector<int> removedCandidates;

            for(int index3 = 0; index3 < 9; index3++) {
                if(candidatesShowupCounter[index3] >= 1 && candidatesShowupCounter[index3] <= 4) {
                    addedCandidates.push_back(index3);
                }
                else {
                    removedCandidates.push_back(index3);
                }
            }

            if(addedCandidates.size() == 4) {
                vector<int> addedCells;

                for(int index3 = 0; index3 < 9; index3++) {
                    int candidateConfirmationCounter = 0;

                    for(int index4 = 0; index4 < addedCandidates.size(); index4++) {
                        if(candidatesBox[index3 / 3][index3 % 3][addedCandidates[index4]] == 1) {
                            candidateConfirmationCounter++;
                        }
                    }

                    if(candidateConfirmationCounter >= 1) {
                        addedCells.push_back(index3);
                    }
                }

                if(addedCells.size() == 4) {
                    for(int index3 = 0; index3 < addedCells.size(); index3++) {
                        for(int index4 = 0; index4 < addedCandidates.size(); index4++) {
                            if(candidatesBox[addedCells[index3] / 3][addedCells[index3] % 3][addedCandidates[index4]] == 1) {
                                candidatesToStay.push_back(make_tuple(make_tuple(index1, addedCells[index3]), addedCandidates[index4]));
                            }
                        }

                        for(int index4 = 0; index4 < removedCandidates.size(); index4++) {
                            if(candidatesBox[addedCells[index3] / 3][addedCells[index3] % 3][removedCandidates[index4]] == 1) {
                                candidatesToRemove.push_back(make_tuple(make_tuple(index1, addedCells[index3]), removedCandidates[index4]));
                            }
                        }
                    }

                    if(candidatesToRemove.size() > 0) {
                        return make_tuple(true, candidatesToStay, candidatesToRemove);
                    }

                    candidatesToStay.clear();
                }

                addedCells.clear();
            }

            addedCandidates.clear();
            removedCandidates.clear();
        }
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}



tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> boxRowReduction(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1 = index1 + 3) {
        for(int index2 = 0; index2 < 9; index2 = index2 + 3) {
            int candidatesBox[3][3][9];
            fill_n(&candidatesBox[0][0][0], sizeof(candidatesBox) / sizeof(***candidatesBox), 0);

            getCandidatesBox(candidates, index1, index2, candidatesBox);

            int candidatesShowupCounter[9];

            fill_n(&candidatesShowupCounter[0], sizeof(candidatesShowupCounter) / sizeof(*candidatesShowupCounter), 0);

            for(int index3 = 0; index3 < 9; index3++) {
                for(int index4 = 0; index4 < 9; index4++) {
                    if(candidatesBox[index3 / 3][index3 % 3][index4] == 1) {
                        candidatesShowupCounter[index4]++;
                    }
                }
            }

            vector<int> addedCandidates;

            for(int index3 = 0; index3 < 9; index3++) {
                if(candidatesShowupCounter[index3] == 2 || candidatesShowupCounter[index3] == 3) {
                    addedCandidates.push_back(index3);
                }
            }

            if(addedCandidates.size() > 0) {
                for(int index3 = 0; index3 < addedCandidates.size(); index3++) {
                    vector<int> positions;

                    for(int index4 = 0; index4 < 9; index4++) {
                        if(candidatesBox[index4 / 3][index4 % 3][addedCandidates[index3]] == 1) {
                            positions.push_back(index4);
                        }
                    }

                    bool sameRow = true;

                    for(int index4 = 0; index4 < positions.size() - 1; index4++) {
                        if(positions[index4] / 3 != positions[index4 + 1] / 3) {
                            sameRow = false;
                        }
                    }

                    if(sameRow == true) {
                        int candidatesRow[9][9];
                        fill_n(&candidatesRow[0][0], sizeof(candidatesRow) / sizeof(**candidatesRow), 0);

                        getCandidatesRow(candidates, index1 + positions[0] / 3, candidatesRow);

                        for(int index4 = 0; index4 < 9; index4++) {
                            if(candidatesRow[index4][addedCandidates[index3]] == 1) {
                                if(index4 / 3 == index2 / 3) {
                                    candidatesToStay.push_back(make_tuple(make_tuple(index1 + positions[0] / 3, index4), addedCandidates[index3]));
                                }
                                else {
                                    candidatesToRemove.push_back(make_tuple(make_tuple(index1 + positions[0] / 3, index4), addedCandidates[index3]));
                                }
                            }
                        }

                        if(candidatesToRemove.size() > 0) {
                            return make_tuple(true, candidatesToStay, candidatesToRemove);
                        }

                        candidatesToStay.clear();
                    }

                    positions.clear();
                }
            }

            addedCandidates.clear();
        }
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> boxColumnReduction(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1 = index1 + 3) {
        for(int index2 = 0; index2 < 9; index2 = index2 + 3) {
            int candidatesBox[3][3][9];
            fill_n(&candidatesBox[0][0][0], sizeof(candidatesBox) / sizeof(***candidatesBox), 0);

            getCandidatesBox(candidates, index1, index2, candidatesBox);

            int candidatesShowupCounter[9];

            fill_n(&candidatesShowupCounter[0], sizeof(candidatesShowupCounter) / sizeof(*candidatesShowupCounter), 0);

            for(int index3 = 0; index3 < 9; index3++) {
                for(int index4 = 0; index4 < 9; index4++) {
                    if(candidatesBox[index3 / 3][index3 % 3][index4] == 1) {
                        candidatesShowupCounter[index4]++;
                    }
                }
            }

            vector<int> addedCandidates;

            for(int index3 = 0; index3 < 9; index3++) {
                if(candidatesShowupCounter[index3] == 2 || candidatesShowupCounter[index3] == 3) {
                    addedCandidates.push_back(index3);
                }
            }

            if(addedCandidates.size() > 0) {
                for(int index3 = 0; index3 < addedCandidates.size(); index3++) {
                    vector<int> positions;

                    for(int index4 = 0; index4 < 9; index4++) {
                        if(candidatesBox[index4 / 3][index4 % 3][addedCandidates[index3]] == 1) {
                            positions.push_back(index4);
                        }
                    }

                    bool sameColumn = true;

                    for(int index4 = 0; index4 < positions.size() - 1; index4++) {
                        if(positions[index4] % 3 != positions[index4 + 1] % 3) {
                            sameColumn = false;
                        }
                    }

                    if(sameColumn == true) {
                        int candidatesColumn[9][9];
                        fill_n(&candidatesColumn[0][0], sizeof(candidatesColumn) / sizeof(**candidatesColumn), 0);

                        getCandidatesColumn(candidates, index2 + positions[0] % 3, candidatesColumn);

                        for(int index4 = 0; index4 < 9; index4++) {
                            if(candidatesColumn[index4][addedCandidates[index3]] == 1) {
                                if(index4 / 3 == index1 / 3) {
                                    candidatesToStay.push_back(make_tuple(make_tuple(index4, index2 + positions[0] % 3), addedCandidates[index3]));
                                }
                                else {
                                    candidatesToRemove.push_back(make_tuple(make_tuple(index4, index2 + positions[0] % 3), addedCandidates[index3]));
                                }
                            }
                        }

                        if(candidatesToRemove.size() > 0) {
                            return make_tuple(true, candidatesToStay, candidatesToRemove);
                        }

                        candidatesToStay.clear();
                    }

                    positions.clear();
                }
            }

            addedCandidates.clear();
        }
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}



tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> rowBoxReduction(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1++) {
        int candidatesRow[9][9];
        fill_n(&candidatesRow[0][0], sizeof(candidatesRow) / sizeof(**candidatesRow), 0);

        getCandidatesRow(candidates, index1, candidatesRow);

        int candidatesShowupCounter[9];

        fill_n(&candidatesShowupCounter[0], sizeof(candidatesShowupCounter) / sizeof(*candidatesShowupCounter), 0);

        for(int index2 = 0; index2 < 9; index2++) {
            for(int index3 = 0; index3 < 9; index3++) {
                if(candidatesRow[index2][index3] == 1) {
                    candidatesShowupCounter[index3]++;
                }
            }
        }

        vector<int> addedCandidates;

        for(int index2 = 0; index2 < 9; index2++) {
            if(candidatesShowupCounter[index2] == 2 || candidatesShowupCounter[index2] == 3) {
                addedCandidates.push_back(index2);
            }
        }

        if(addedCandidates.size() > 0) {
            for(int index2 = 0; index2 < addedCandidates.size(); index2++) {
                vector<int> positions;

                for(int index3 = 0; index3 < 9; index3++) {
                    if(candidatesRow[index3][addedCandidates[index2]] == 1) {
                        positions.push_back(index3);
                    }
                }

                bool sameBox = true;

                for(int index3 = 0; index3 < positions.size() - 1; index3++) {
                    if(positions[index3] / 3 != positions[index3 + 1] / 3) {
                        sameBox = false;
                    }
                }

                if(sameBox == true) {
                    int candidatesBox[3][3][9];
                    fill_n(&candidatesBox[0][0][0], sizeof(candidatesBox) / sizeof(***candidatesBox), 0);

                    getCandidatesBox(candidates, index1, positions[0], candidatesBox);

                    for(int index3 = 0; index3 < 9; index3++) {
                        if(candidatesBox[index3 / 3][index3 % 3][addedCandidates[index2]] == 1) {
                            if(index1 % 3 == (index3 / 3) % 3) {
                                candidatesToStay.push_back(make_tuple(make_tuple(index1 - index1 % 3 + index3 / 3, positions[0] - positions[0] % 3 + index3 % 3), addedCandidates[index2]));
                            }
                            else {
                                candidatesToRemove.push_back(make_tuple(make_tuple(index1 - index1 % 3 + index3 / 3, positions[0] - positions[0] % 3 + index3 % 3), addedCandidates[index2]));
                            }
                        }
                    }

                    if(candidatesToRemove.size() > 0) {
                        return make_tuple(true, candidatesToStay, candidatesToRemove);
                    }

                    candidatesToStay.clear();
                }

                positions.clear();
            }
        }

        addedCandidates.clear();
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> columnBoxReduction(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 9; index1++) {
        int candidatesColumn[9][9];
        fill_n(&candidatesColumn[0][0], sizeof(candidatesColumn) / sizeof(**candidatesColumn), 0);

        getCandidatesColumn(candidates, index1, candidatesColumn);

        int candidatesShowupCounter[9];

        fill_n(&candidatesShowupCounter[0], sizeof(candidatesShowupCounter) / sizeof(*candidatesShowupCounter), 0);

        for(int index2 = 0; index2 < 9; index2++) {
            for(int index3 = 0; index3 < 9; index3++) {
                if(candidatesColumn[index2][index3] == 1) {
                    candidatesShowupCounter[index3]++;
                }
            }
        }

        vector<int> addedCandidates;

        for(int index2 = 0; index2 < 9; index2++) {
            if(candidatesShowupCounter[index2] == 2 || candidatesShowupCounter[index2] == 3) {
                addedCandidates.push_back(index2);
            }
        }

        if(addedCandidates.size() > 0) {
            for(int index2 = 0; index2 < addedCandidates.size(); index2++) {
                vector<int> positions;

                for(int index3 = 0; index3 < 9; index3++) {
                    if(candidatesColumn[index3][addedCandidates[index2]] == 1) {
                        positions.push_back(index3);
                    }
                }

                bool sameBox = true;

                for(int index3 = 0; index3 < positions.size() - 1; index3++) {
                    if(positions[index3] / 3 != positions[index3 + 1] / 3) {
                        sameBox = false;
                    }
                }

                if(sameBox == true) {
                    int candidatesBox[3][3][9];
                    fill_n(&candidatesBox[0][0][0], sizeof(candidatesBox) / sizeof(***candidatesBox), 0);

                    getCandidatesBox(candidates, positions[0], index1, candidatesBox);

                    for(int index3 = 0; index3 < 9; index3++) {
                        if(candidatesBox[index3 / 3][index3 % 3][addedCandidates[index2]] == 1) {
                            if(index1 % 3 == index3 % 3) {
                                candidatesToStay.push_back(make_tuple(make_tuple(positions[0] - positions[0] % 3 + index3 / 3, index1 - index1 % 3 + index3 % 3), addedCandidates[index2]));
                            }
                            else {
                                candidatesToRemove.push_back(make_tuple(make_tuple(positions[0] - positions[0] % 3 + index3 / 3, index1 - index1 % 3 + index3 % 3), addedCandidates[index2]));
                            }
                        }
                    }

                    if(candidatesToRemove.size() > 0) {
                        return make_tuple(true, candidatesToStay, candidatesToRemove);
                    }

                    candidatesToStay.clear();
                }

                positions.clear();
            }
        }

        addedCandidates.clear();
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}



tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> xWingRow(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 8; index1++) {
        int candidatesRow1[9][9];
        fill_n(&candidatesRow1[0][0], sizeof(candidatesRow1) / sizeof(**candidatesRow1), 0);

        getCandidatesRow(candidates, index1, candidatesRow1);

        int candidatesShowupCounter1[9];

        fill_n(&candidatesShowupCounter1[0], sizeof(candidatesShowupCounter1) / sizeof(*candidatesShowupCounter1), 0);

        for(int index2 = 0; index2 < 9; index2++) {
            for(int index3 = 0; index3 < 9; index3++) {
                if(candidatesRow1[index2][index3] == 1) {
                    candidatesShowupCounter1[index3]++;
                }
            }
        }

        vector<int> addedCandidates1;

        for(int index2 = 0; index2 < 9; index2++) {
            if(candidatesShowupCounter1[index2] == 2) {
                addedCandidates1.push_back(index2);
            }
        }

        if(addedCandidates1.size() > 0) {
            for(int index2 = index1 + 1; index2 < 9; index2++) {
                int candidatesRow2[9][9];
                fill_n(&candidatesRow2[0][0], sizeof(candidatesRow2) / sizeof(**candidatesRow2), 0);

                getCandidatesRow(candidates, index2, candidatesRow2);

                int candidatesShowupCounter2[9];

                fill_n(&candidatesShowupCounter2[0], sizeof(candidatesShowupCounter2) / sizeof(*candidatesShowupCounter2), 0);

                for(int index3 = 0; index3 < 9; index3++) {
                    for(int index4 = 0; index4 < 9; index4++) {
                        if(candidatesRow2[index3][index4] == 1) {
                            candidatesShowupCounter2[index4]++;
                        }
                    }
                }

                vector<int> addedCandidates2;

                for(int index3 = 0; index3 < 9; index3++) {
                    if(candidatesShowupCounter2[index3] == 2) {
                        addedCandidates2.push_back(index3);
                    }
                }

                if(addedCandidates2.size() > 0) {
                    for(int index3 = 0; index3 < addedCandidates1.size(); index3++) {
                        for(int index4 = 0; index4 < addedCandidates2.size(); index4++) {
                            if(addedCandidates1[index3] == addedCandidates2[index4]) {
                                vector<int> mutualColumns;

                                for(int index5 = 0; index5 < 9; index5++) {
                                    if(candidatesRow1[index5][addedCandidates1[index3]] == 1 && candidatesRow2[index5][addedCandidates1[index3]] == 1) {
                                        mutualColumns.push_back(index5);
                                    }
                                }

                                if(mutualColumns.size() == 2) {
                                    int removingColumn1[9][9];
                                    int removingColumn2[9][9];

                                    fill_n(&removingColumn1[0][0], sizeof(removingColumn1) / sizeof(**removingColumn1), 0);
                                    fill_n(&removingColumn2[0][0], sizeof(removingColumn2) / sizeof(**removingColumn2), 0);

                                    getCandidatesColumn(candidates, mutualColumns[0], removingColumn1);
                                    getCandidatesColumn(candidates, mutualColumns[1], removingColumn2);

                                    for(int index5 = 0; index5 < 9; index5++) {
                                        if(removingColumn1[index5][addedCandidates1[index3]] == 1) {
                                            if(index5 == index1 || index5 == index2) {
                                                candidatesToStay.push_back(make_tuple(make_tuple(index5, mutualColumns[0]), addedCandidates1[index3]));
                                            }
                                            else {
                                                candidatesToRemove.push_back(make_tuple(make_tuple(index5, mutualColumns[0]), addedCandidates1[index3]));
                                            }
                                        }

                                        if(removingColumn2[index5][addedCandidates1[index3]] == 1) {
                                            if(index5 == index1 || index5 == index2) {
                                                candidatesToStay.push_back(make_tuple(make_tuple(index5, mutualColumns[1]), addedCandidates1[index3]));
                                            }
                                            else {
                                                candidatesToRemove.push_back(make_tuple(make_tuple(index5, mutualColumns[1]), addedCandidates1[index3]));
                                            }
                                        }
                                    }

                                    if(candidatesToRemove.size() > 0) {
                                        return make_tuple(true, candidatesToStay, candidatesToRemove);
                                    }

                                    candidatesToStay.clear();
                                }

                                mutualColumns.clear();
                            }
                        }
                    }
                }

                addedCandidates2.clear();
            }
        }

        addedCandidates1.clear();
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}

tuple<bool, vector<tuple<tuple<int, int>, int>>, vector<tuple<tuple<int, int>, int>>> xWingColumn(int puzzle[9][9], int candidates[9][9][9]) {
    vector<tuple<tuple<int, int>, int>> candidatesToStay;
    vector<tuple<tuple<int, int>, int>> candidatesToRemove;

    for(int index1 = 0; index1 < 8; index1++) {
        int candidatesColumn1[9][9];
        fill_n(&candidatesColumn1[0][0], sizeof(candidatesColumn1) / sizeof(**candidatesColumn1), 0);

        getCandidatesColumn(candidates, index1, candidatesColumn1);

        int candidatesShowupCounter1[9];

        fill_n(&candidatesShowupCounter1[0], sizeof(candidatesShowupCounter1) / sizeof(*candidatesShowupCounter1), 0);

        for(int index2 = 0; index2 < 9; index2++) {
            for(int index3 = 0; index3 < 9; index3++) {
                if(candidatesColumn1[index2][index3] == 1) {
                    candidatesShowupCounter1[index3]++;
                }
            }
        }

        vector<int> addedCandidates1;

        for(int index2 = 0; index2 < 9; index2++) {
            if(candidatesShowupCounter1[index2] == 2) {
                addedCandidates1.push_back(index2);
            }
        }

        if(addedCandidates1.size() > 0) {
            for(int index2 = index1 + 1; index2 < 9; index2++) {
                int candidatesColumn2[9][9];
                fill_n(&candidatesColumn2[0][0], sizeof(candidatesColumn2) / sizeof(**candidatesColumn2), 0);

                getCandidatesColumn(candidates, index2, candidatesColumn2);

                int candidatesShowupCounter2[9];

                fill_n(&candidatesShowupCounter2[0], sizeof(candidatesShowupCounter2) / sizeof(*candidatesShowupCounter2), 0);

                for(int index3 = 0; index3 < 9; index3++) {
                    for(int index4 = 0; index4 < 9; index4++) {
                        if(candidatesColumn2[index3][index4] == 1) {
                            candidatesShowupCounter2[index4]++;
                        }
                    }
                }

                vector<int> addedCandidates2;

                for(int index3 = 0; index3 < 9; index3++) {
                    if(candidatesShowupCounter2[index3] == 2) {
                        addedCandidates2.push_back(index3);
                    }
                }

                if(addedCandidates2.size() > 0) {
                    for(int index3 = 0; index3 < addedCandidates1.size(); index3++) {
                        for(int index4 = 0; index4 < addedCandidates2.size(); index4++) {
                            if(addedCandidates1[index3] == addedCandidates2[index4]) {
                                vector<int> mutualRows;

                                for(int index5 = 0; index5 < 9; index5++) {
                                    if(candidatesColumn1[index5][addedCandidates1[index3]] == 1 && candidatesColumn2[index5][addedCandidates1[index3]] == 1) {
                                        mutualRows.push_back(index5);
                                    }
                                }

                                if(mutualRows.size() == 2) {
                                    int removingRow1[9][9];
                                    int removingRow2[9][9];

                                    fill_n(&removingRow1[0][0], sizeof(removingRow1) / sizeof(**removingRow1), 0);
                                    fill_n(&removingRow2[0][0], sizeof(removingRow2) / sizeof(**removingRow2), 0);

                                    getCandidatesRow(candidates, mutualRows[0], removingRow1);
                                    getCandidatesRow(candidates, mutualRows[1], removingRow2);

                                    for(int index5 = 0; index5 < 9; index5++) {
                                        if(removingRow1[index5][addedCandidates1[index3]] == 1) {
                                            if(index5 == index1 || index5 == index2) {
                                                candidatesToStay.push_back(make_tuple(make_tuple(mutualRows[0], index5), addedCandidates1[index3]));
                                            }
                                            else {
                                                candidatesToRemove.push_back(make_tuple(make_tuple(mutualRows[0], index5), addedCandidates1[index3]));
                                            }
                                        }

                                        if(removingRow2[index5][addedCandidates1[index3]] == 1) {
                                            if(index5 == index1 || index5 == index2) {
                                                candidatesToStay.push_back(make_tuple(make_tuple(mutualRows[1], index5), addedCandidates1[index3]));
                                            }
                                            else {
                                                candidatesToRemove.push_back(make_tuple(make_tuple(mutualRows[1], index5), addedCandidates1[index3]));
                                            }
                                        }
                                    }

                                    if(candidatesToRemove.size() > 0) {
                                        return make_tuple(true, candidatesToStay, candidatesToRemove);
                                    }

                                    candidatesToStay.clear();
                                }

                                mutualRows.clear();
                            }
                        }
                    }
                }

                addedCandidates2.clear();
            }
        }

        addedCandidates1.clear();
    }

    return make_tuple(false, candidatesToStay, candidatesToRemove);
}