#include "CurrentMove.h"
#include "Game.h"
extern bool isPlayer1Turn;
extern map<string, QLabel*> map_s_Q;
extern Game game1;


// Constuctor of CurrentMove
CurrentMove::CurrentMove() {
    moveFromButtonName = "";
    moveToButtonName = "";
    movingLabelPtr = nullptr;
}

// The implementation of the 'pickPiece' method from Class Move.
void CurrentMove::pickPiece(std::string pickedButtonName, QLabel*& pickedLabelPtr) {
    if (pickedLabelPtr != nullptr) { // When the label exists...
        string pickedLabelcolor = pickedLabelPtr->objectName().toStdString().substr(0,1);
        if (isPlayer1Turn && pickedLabelcolor== "y") { // When it is Player1's turn of picked Label is player2's, thow an exception.
            throw invalid_argument("This is Player1's turn!");
        } else if (!isPlayer1Turn && pickedLabelcolor== "b") { // When it is Player2's turn of picked Label is Player1, thow an exception.
            throw invalid_argument("This is Player2's turn!");
        } else {
            setMoveFromButtonName(pickedButtonName); // Store the name as starting point of the move.
            setMovingLabelPtr(pickedLabelPtr); // Store the pointer of moved piece.
        }
    } else { // If the label does not exist, throw and exception.
        throw invalid_argument("You clicked empty space!");
    }
}

// The implementation of the 'movePiece' method from Class Move.
void CurrentMove::movePiece(string pickedButtonName){
    // Extract the coordinate of the starting point and potential reaching point from button names.
    int fromX = stoi(getMoveFromButtonName().substr(2,1));
    int fromY = stoi(getMoveFromButtonName().substr(4,1));

    int toX = stoi(pickedButtonName.substr(2,1));
    int toY = stoi(pickedButtonName.substr(4,1));

    // If the move is not diagoanl move, throw an exception.
    if (abs(toX-fromX) != abs(toY-fromY)) {throw invalid_argument("Only diagonal move is allowed");}

    // If player try to jump more than 3 diagonal squares at once, throw an exception.
    if (abs(toX-fromX) >= 3){
        throw invalid_argument("This is invalid movement!");
    }
    // If the label is not King...
    if (movingLabelPtr->property("king") == false){
        // If the moveing is not, forward move, throw an exception.
        if (isPlayer1Turn? toY>=fromY: toY<=fromY){
            throw invalid_argument("Move non-king piece forward!");
        }
        // If user try to move 2 diagonal squares...
        if (abs(toX-fromX) ==2 && abs(toY-fromY)==2){
            string midX = to_string(fromX+(int)(toX-fromX)/2);
            string midY = to_string(fromY+(int)(toY-fromY)/2);
            string midButtonName = "B_";
            midButtonName.append(midX);
            midButtonName.append("_");
            midButtonName.append(midY);
            // Check the label located at the very button in between.
            QLabel* midLabelPtr = map_s_Q.at(midButtonName);

            // If nothing is located on the button, throw an exception.
            if (midLabelPtr == nullptr) {
                throw invalid_argument("No piece in between!");
            } //early return

            // If the label located on the button in between has different color, remove it and move the picked piece.
            string color = midLabelPtr->objectName().toStdString().substr(0,1);
            moveToButtonName = pickedButtonName;
            if (isPlayer1Turn && color=="y"){
                movingLabelPtr->move(35+(toX-1)*64, 30+(toY-1)*64);
                QLabel* tempLabelPtr = map_s_Q.at(moveFromButtonName);
                map_s_Q[moveFromButtonName] = nullptr;
                map_s_Q[moveToButtonName] = tempLabelPtr;

                map_s_Q.at(midButtonName)->setVisible(false);
                map_s_Q[midButtonName] = nullptr;
                game1.increaseHitPieceCount_player1(); // Increase the hit count.
                return;
            } else if (!isPlayer1Turn && color=="b") {
                movingLabelPtr->move(35+(toX-1)*64, 30+(toY-1)*64);
                QLabel* tempLabelPtr = map_s_Q.at(moveFromButtonName);
                map_s_Q[moveFromButtonName] = nullptr;
                map_s_Q[moveToButtonName] = tempLabelPtr;

                map_s_Q.at(midButtonName)->setVisible(false);
                map_s_Q[midButtonName] = nullptr;
                game1.increaseHitPieceCount_player2(); // Increase the hit count
                return;
            //  If not, throw an exception. (When trying to eat up their own piece.)
            } else{throw invalid_argument("This is invalid movement!");}
        }

        // If not filered by the conditions above, it is simply a move(not catching any piece).
        setMoveToButtonName(pickedButtonName);
        getMovingLabelPtr()->move(35+(toX-1)*64, 30+(toY-1)*64);
        QLabel* tempLabelPtr = map_s_Q.at(moveFromButtonName);
        map_s_Q[getMoveFromButtonName()] = nullptr;
        map_s_Q[getMoveToButtonName()] = tempLabelPtr;
        return;
    }
    else { // When the piece is King....
        if (abs(toX-fromX) ==2 && abs(toY-fromY)==2){ // If user try to move 2 diagonal squares...
            string midX = to_string(fromX+(int)(toX-fromX)/2);
            string midY = to_string(fromY+(int)(toY-fromY)/2);
            string midButtonName = "B_";
            midButtonName.append(midX);
            midButtonName.append("_");
            midButtonName.append(midY);
            QLabel* midLabelPtr = map_s_Q.at(midButtonName);
            if (midLabelPtr == nullptr) {
                throw invalid_argument("No piece in between!");
            }
            // If the label located on the button in between has different color, remove it and move the picked picked.
            if (midLabelPtr != nullptr) {
                string color = midLabelPtr->objectName().toStdString().substr(0,1);
                setMoveToButtonName(pickedButtonName);
                if (isPlayer1Turn && color=="y"){
                    getMovingLabelPtr()->move(35+(toX-1)*64, 30+(toY-1)*64);
                    QLabel* tempLabelPtr = map_s_Q.at(moveFromButtonName);
                    map_s_Q[getMoveFromButtonName()] = nullptr;
                    map_s_Q[getMoveToButtonName()] = tempLabelPtr;

                    map_s_Q.at(midButtonName)->setVisible(false);
                    map_s_Q[midButtonName] = nullptr;
                    game1.increaseHitPieceCount_player1(); // Increate the count.
                    return;
                } else if (!isPlayer1Turn && color=="b") {
                    movingLabelPtr->move(35+(toX-1)*64, 30+(toY-1)*64);
                    QLabel* tempLabelPtr = map_s_Q.at(getMoveFromButtonName());
                    map_s_Q[getMoveFromButtonName()] = nullptr;
                    map_s_Q[getMoveToButtonName()] = tempLabelPtr;

                    map_s_Q.at(midButtonName)->setVisible(false);
                    map_s_Q[midButtonName] = nullptr;
                    game1.increaseHitPieceCount_player2(); // Increate the count.
                    return;
                }
            }
        }
        // If not filered by the conditions above, it is simply a move(not catching any piece).
        setMoveToButtonName(pickedButtonName);
        getMovingLabelPtr()->move(35+(toX-1)*64, 30+(toY-1)*64);
        QLabel* tempLabelPtr = map_s_Q.at(getMoveFromButtonName());
        map_s_Q[getMoveFromButtonName()] = nullptr;
        map_s_Q[getMoveToButtonName()] = tempLabelPtr;
        return;
    }
}
