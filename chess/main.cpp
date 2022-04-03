
#include <iostream>
#include <windows.h>

using namespace std;

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/freeglut.h>
    #include <GL/glut.h>
#endif // GLUT Library
//Model
#include "Model.h"
//Chess Game
#include "Chess/Game.h"
//tailles des fenettres
#define WINDOW_WIDTH GetSystemMetrics(SM_CXSCREEN)
#define WINDOW_HEIGHT GetSystemMetrics(SM_CYSCREEN)
#define WINDOW_POS_X 0
#define WINDOW_POS_Y 0


#define BUTTON_X -100
#define BUTTON_Y -100
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 75


//  Prototype
void keyFunction(unsigned char key, int x, int y);
void zoom(int key, int x, int y);



//  Variable de la caméra 

GLfloat     eyeX = 5.0, eyeY = 0.0, eyeZ = -5.0,
            centerX = 0.0, centerY = 0.0, centerZ =0.0,
            upX = 0.0, upY = 0.0, upZ = -1.0;


//  Valeur de la fonction perspective
GLfloat     fovy = 50.0, zNear = 0.1, zFar = 20.0;


//  Lumière
GLfloat     position[] = {0.0f, 0.0f, 100.0f, 0.0f};
GLfloat     diffusion[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat     normal_board[] = {0.0f, 0.0f, 1.0f};
GLfloat     normal_valid_move[] = {0.0f, 0.0f, -1.0f};
float       ang = 0;
GLfloat mat_diffusion[] = {0.8, 0.8, 0.8, 1.0};
GLfloat mat_specular[] = {0.1, 0.1, 0.1, 1.0};


//  Gestion de la vue

GLfloat     screen_ratio, zoomOut = 2;


//  Modèles des pieces 3D


Model   Pawn("model/Pawn.obj");
Model   Rook("model/Rook.obj");
Model   Knight("model/Knight.obj");
Model   Bishop("model/Bishop.obj");
Model   King("model/King.obj");
Model   Queen("model/Queen.obj");

/*
Model   Pawn("../Debug/model/Pawn.obj");
Model   Rook("../Debug/model/Rook.obj");
Model   Knight("../Debug/model/Knight.obj");
Model   Bishop("../Debug/model/Bishop.obj");
Model   King("../Debug/model/King.obj");
Model   Queen("../Debug/model/Queen.obj");


Model   Pawn("../Debug/Obj2/Pawn.obj");
Model   Rook("../Debug/Obj2/Rook.obj");
Model   Knight("../Debug/Obj2/Knight.obj");
Model   Bishop("../Debug/Obj2/Bishop.obj");
Model   King("../Debug/Obj2/King.obj");
Model   Queen("../Debug/Obj2/Queen.obj");
*/

//C:\JeuDechec\Jeu - D - Echec\chess\Debug\model

//  Pre-lancement

bool pressed = false;


//  Charget du jeu

Game *chess;
void newGame();

//  Variable utile lors du fonctionement 
bool    inGame = false, verify = false;
int     selectedRow = 1, selectedCol = 1;
int     moveToRow = 1, moveToCol = 1;
bool    selected = false;
bool    board_rotating = true;
int     rotation = 0;
bool    check = false, checkMate = false;
bool    closeGame = false;
bool	needPromote = false;


//  Sommets de l'échiquier
GLfloat     chessBoard[12][3] = {{-4.0, -4.0, 0.5},
                                {-4.0,  4.0, 0.5},
                                { 4.0,  4.0, 0.5},
                                { 4.0, -4.0, 0.5},

                                {-4.5, -4.5, 0.5},
                                {-4.5,  4.5, 0.5},
                                { 4.5,  4.5, 0.5},
                                { 4.5, -4.5, 0.5},

                                {-5.0, -5.0, 0.0},
                                {-5.0,  5.0, 0.0},
                                { 5.0,  5.0, 0.0},
                                { 5.0, -5.0, 0.0}};


//  
void showWord( int x, int y, string word)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WINDOW_WIDTH/2, WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, WINDOW_HEIGHT/2, 0, 1);
    //glutFullScreen();
    glutShowWindow();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    int l,i;

    l=word.length(); //nb de char dans le String  
    glRasterPos2i(x, y); //position dans la fenêtre 
    glColor3f(0.545, 0.271, 0.075);

    for( i=0; i < l; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, word[i]); //affichage 1 par 1
    }
}


//  Dessine un carré de l'Échiquier
void drawMoveToSquare()
{
    float r = 1.0*(moveToRow-5), c = 1.0*(moveToCol-5);
    if(selected)
    {
        glPushMatrix();
            glColor3f(0.5f, 1.0f, 0.0f);
            glTranslatef(r, c, 0.502f);
            glScalef(0.98f, 0.98f, 1.0f);
                glBegin(GL_TRIANGLES);
                    glNormal3fv(normal_valid_move);
                    glVertex3f(0.0f, 0.0f, 0.0f);
                    glVertex3f(1.0f, 1.0f, 0.0f);
                    glVertex3f(0.0f, 1.0f, 0.0f);
                    glVertex3f(0.0f, 0.0f, 0.0f);
                    glVertex3f(1.0f, 1.0f, 0.0f);
                    glVertex3f(1.0f, 0.0f, 0.0f);
                glEnd();
        glPopMatrix();
    }
    glColor3f(0, 0, 0);
}


//  Dessine un échiquier en utilisant les points du tableau "chessBoard".
void drawChessBoard()
{
    glPushMatrix();
        glNormal3fv(normal_valid_move);
        glBegin(GL_QUADS);
            glColor3f(0.5, 0.5, 0.5);
            for(int i=8; i<12; i++) 
                glVertex3fv(chessBoard[i]);
        glEnd();
        //Affichage de l'échiquié 
        glBegin(GL_QUADS);
            glColor3f(0.55, 0.24, 0.09);
            glColor3f(0.803, 0.522, 0.247);
            glVertex3fv(chessBoard[0]);
            glColor3f(0.545, 0.271, 0.075);
            glVertex3fv(chessBoard[4]);
            glColor3f(0.545, 0.271, 0.075);
            glVertex3fv(chessBoard[5]);
            glColor3f(0.803, 0.522, 0.247);
            glVertex3fv(chessBoard[1]);
        glEnd();
        glBegin(GL_QUADS);
            glColor3f(0.803, 0.522, 0.247);
            glVertex3fv(chessBoard[1]);
            glColor3f(0.545, 0.271, 0.075);
            glVertex3fv(chessBoard[5]);
            glColor3f(0.545, 0.271, 0.075);
            glVertex3fv(chessBoard[6]);
            glColor3f(0.803, 0.522, 0.247);
            glVertex3fv(chessBoard[2]);
        glEnd();
        glBegin(GL_QUADS);
            glColor3f(0.803, 0.522, 0.247);
            glVertex3fv(chessBoard[2]);
            glColor3f(0.545, 0.271, 0.075);
            glVertex3fv(chessBoard[6]);
            glColor3f(0.545, 0.271, 0.075);
            glVertex3fv(chessBoard[7]);
            glColor3f(0.803, 0.522, 0.247);
            glVertex3fv(chessBoard[3]);
        glEnd();
        glBegin(GL_QUADS);
            glColor3f(0.803, 0.522, 0.247);
            glVertex3fv(chessBoard[3]);
            glColor3f(0.545, 0.271, 0.075);
            glVertex3fv(chessBoard[7]);
            glColor3f(0.545, 0.271, 0.075);
            glVertex3fv(chessBoard[4]);
            glColor3f(0.803, 0.522, 0.247);
            glVertex3fv(chessBoard[0]);
        glEnd();

        glBegin(GL_QUADS);
            glColor3f(1.0, 0.95, 0.9);
            glColor3f(0.545, 0.271, 0.075);
            glVertex3fv(chessBoard[4]);
            glColor3f(1.000, 1.000, 1.000);
            glVertex3fv(chessBoard[8]);
            glColor3f(1.000, 1.000, 1.000);
            glVertex3fv(chessBoard[9]);
            glColor3f(0.545, 0.271, 0.075);
            glVertex3fv(chessBoard[5]);
        glEnd();
        glBegin(GL_QUADS);
            glColor3f(0.545, 0.271, 0.075);
            glVertex3fv(chessBoard[5]);
            glColor3f(1.000, 1.000, 1.000);
            glVertex3fv(chessBoard[9]);
            glColor3f(1.000, 1.000, 1.000);
            glVertex3fv(chessBoard[10]);
            glColor3f(0.545, 0.271, 0.075);
            glVertex3fv(chessBoard[6]);
        glEnd();
        glBegin(GL_QUADS);
            glColor3f(0.545, 0.271, 0.075);
            glVertex3fv(chessBoard[6]);
            glColor3f(1.000, 1.000, 1.000);
            glVertex3fv(chessBoard[10]);
            glColor3f(1.000, 1.000, 1.000);
            glVertex3fv(chessBoard[11]);
            glColor3f(0.545, 0.271, 0.075);
            glVertex3fv(chessBoard[7]);
        glEnd();
        glBegin(GL_QUADS);
            glColor3f(0.545, 0.271, 0.075);
            glVertex3fv(chessBoard[7]);
            glColor3f(1.000, 1.000, 1.000);
            glVertex3fv(chessBoard[11]);
            glColor3f(1.000, 1.000, 1.000);
            glVertex3fv(chessBoard[8]);
            glColor3f(0.545, 0.271, 0.075);
            glVertex3fv(chessBoard[4]);
        glEnd();
    glPopMatrix();
    glColor3f(0, 0, 0);
}

//  Dessine les cases 
void drawBoardSquares()
{
    float r, c;
    for(int row = 1 ; row <= 8 ; row++)
    {
        for(int col = 1 ; col <= 8 ; col++)
        {
            r = 1.0*(row-5);
            c = 1.0*(col-5);
            if(row == selectedRow && col == selectedCol)
            {
                if(selected) glColor3f(0.33f, 0.420f, 0.184f);
                else if(chess->isSquareOccupied(selectedRow, selectedCol))
                    if(chess->getPieceColor(selectedRow, selectedCol) == chess->getTurnColor())
                        glColor3f(0.0f, 0.5f, 0.0f);
                    else glColor3f(1.0f, 0.0f, 0.0f);
                else glColor3f(0.3f, 0.7f, 0.5f);
            }
            else if((row + col) & 1) glColor3f(1.0, 1.0, 1.0);
            else glColor3f(0.0, 0.0, 0.0);
            glPushMatrix();
                glTranslatef(r, c, 0.5f);
                glBegin(GL_TRIANGLES);
                    glNormal3fv(normal_board);
                    glVertex3f(0.0f, 0.0f, 0.0f);
                    glVertex3f(1.0f, 1.0f, 0.0f);
                    glVertex3f(0.0f, 1.0f, 0.0f);
                    glVertex3f(0.0f, 0.0f, 0.0f);
                    glVertex3f(1.0f, 1.0f, 0.0f);
                    glVertex3f(1.0f, 0.0f, 0.0f);
                glEnd();
            glPopMatrix();
        }
    }
    glColor3f(0, 0, 0);
}


//  Dessine les mouvements valides de la pièce sélectionnée
void drawValidMoves()
{
    if(selected)
    {
        std::vector<Move> validMoves = chess->getValidMoves(selectedRow, selectedCol);
        int vec_size = validMoves.size(), row, col;
        for(int id = 0; id < vec_size; id++)
        {
            row = validMoves[id].getDestinationPosition().first;
            col = validMoves[id].getDestinationPosition().second;
            switch(validMoves[id].getType())
            {
                case MoveType::NORMAL:
                    glColor3f(0.8f, 1.0f, 0.6f);
                    break;
                case MoveType::CAPTURE:
                    glColor3f(1.0f, 0.0f, 0.0f);
                    break;
                case MoveType::EN_PASSANT:
                    glColor3f(0.8f, 1.0f, 0.6f);
                    break;
                case MoveType::CASTLING:
                    glColor3f(0.196f, 0.804f, 0.196f);
                    break;
            }
            float r = 1.0*(row-5), c = 1.0*(col-5);
            glPushMatrix();
                    glTranslatef(r, c, 0.501);
                    glScalef(0.99f, 0.99f, 1.0f);
                    glBegin(GL_TRIANGLES);
                        glNormal3fv(normal_valid_move);
                        glVertex3f(0.0f, 0.0f, 0.0f);
                        glVertex3f(1.0f, 1.0f, 0.0f);
                        glVertex3f(0.0f, 1.0f, 0.0f);
                        glVertex3f(0.0f, 0.0f, 0.0f);
                        glVertex3f(1.0f, 1.0f, 0.0f);
                        glVertex3f(1.0f, 0.0f, 0.0f);
                    glEnd();
            glPopMatrix();
        }
    }
    glColor3f(0, 0, 0);
}


//  Dessine les pièces d'échecs sur l'échiquier
void drawChessPieces()
{
    float z;
    for(int row = 1; row <= 8; row++)
    {
        for(int col = 1; col <= 8; col++)
        {
            if(chess->isSquareOccupied(row, col))
            {
                glPushMatrix();
                    if(selected && row == selectedRow && col == selectedCol) z = 1.0;
                    else z = 0.5;
                    glTranslatef((row - 5) * 1.0f + 0.5f, (col - 5) * 1.0f + 0.5f, z);
                    //Tailles des pieces  
                    glScalef(0.05f, 0.05f, 0.05f);
                    switch(chess->getPieceColor(row, col))
                    {
                        //Emplacement des pieces blanches
                        case PieceColor::WHITE:
                            glRotatef(90, 90, 0.0f, 1.0f);
                            glColor3f(0.9f, 0.9f, 0.9f);
                            break;
                        
                        //Emplacement des pieces noires
                        case PieceColor::BLACK:
                            glRotatef(-90, -90, 0.0f, 1.0f);
                            glColor3f(0.1f, 0.1f, 0.1f);
                            break;
                    }
                    switch(chess->getPiece(row, col)->getType())
                    {
                        
                        case PieceType::PAWN: Pawn.Draw(); break;
                        case PieceType::ROOK: Rook.Draw(); break;
                        case PieceType::KNIGHT: Knight.Draw(); break;
                        case PieceType::BISHOP: Bishop.Draw(); break;
                        case PieceType::QUEEN: Queen.Draw(); break;
                        case PieceType::KING: King.Draw(); break;
                    }
                glPopMatrix();
            }
        }
    }
    glColor3f(0, 0, 0);
}

//  Selection de la piece avec les touches
void key_Z_pressed(PieceColor color)
{
    switch(color)
    {
        case PieceColor::WHITE:
            if(!selected && selectedRow < 8) selectedRow++;
            if(selected && moveToRow < 8) moveToRow++;
            break;
        case PieceColor::BLACK:
            if(!selected && selectedRow > 1) selectedRow--;
            if(selected && moveToRow > 1) moveToRow--;
            break;
    }
}

void key_D_pressed(PieceColor color)
{
    switch(color)
    {
        case PieceColor::WHITE:
            if(!selected && selectedCol < 8) selectedCol++;
            if(selected && moveToCol < 8) moveToCol++;
            break;
        case PieceColor::BLACK:
            if(!selected && selectedCol > 1) selectedCol--;
            if(selected && moveToCol > 1) moveToCol--;
            break;
    }
}

void key_S_pressed(PieceColor color)
{
    switch(color)
    {
        case PieceColor::WHITE:
            if(!selected && selectedRow > 1) selectedRow--;
            if(selected && moveToRow > 1) moveToRow--;
            break;
        case PieceColor::BLACK:
            if(!selected && selectedRow < 8) selectedRow++;
            if(selected && moveToRow < 8) moveToRow++;
            break;
    }
}

void key_Q_pressed(PieceColor color)
{
    switch(color)
    {
        case PieceColor::WHITE:
            if(!selected && selectedCol > 1) selectedCol--;
            if(selected && moveToCol > 1) moveToCol--;
            break;
        case PieceColor::BLACK:
            if(!selected && selectedCol < 8) selectedCol++;
            if(selected && moveToCol < 8) moveToCol++;
            break;
    }
}

void updateTurn(PieceColor color)
{
    switch(color)
    {
        case PieceColor::WHITE:
            selectedRow = 1;
            selectedCol = 8;
            break;
        case PieceColor::BLACK:
            selectedRow = 8;
            selectedCol = 1;
            break;
    }
}

//Rotation du changement de joueur 
void doRotationBoard(PieceColor color)
{
    switch(color)
    {
        case PieceColor::WHITE:
            if(rotation < 180) rotation += 180;
            else board_rotating = false;
            break;
        case PieceColor::BLACK:
            if(rotation < 360) rotation += 180;
            else
            {
                rotation = 0;
                board_rotating = false;
            }
            break;
    }
}

//  tout est dans le nom en vrai 
void endOfTurn()
{
    selected = false;
    needPromote = false;
	check = false;
	chess->nextTurn();
	if(chess->inCheckMateState())
	{
		checkMate = true;
	}
	else if(chess->inCheckState())
	{
		check = true;
	}
	board_rotating = true;
	updateTurn(chess->getTurnColor());
}

void showWordRGB(int x, int y, string word, int r, int g, int b)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WINDOW_WIDTH / 2, WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, WINDOW_HEIGHT / 2, 0, 1);
    //glutFullScreen();
    glutShowWindow();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    int l, i;

    l = word.length(); //nb de char dans le String  
    glRasterPos2i(x, y); //position dans la fenêtre 
    glColor3f(r, g, b);

    for (i = 0; i < l; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, word[i]); //affichage 1 par 1
    }
}

void displayFunction()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(inGame)
    {
        showWordRGB(-WINDOW_WIDTH/2, (WINDOW_HEIGHT/3)+120, "Controlle:", 0, 0, 0);
        showWordRGB(-WINDOW_WIDTH/2, (WINDOW_HEIGHT/3)+100, "N pour jouer une nouvelle partie", 0, 0, 0);
        showWordRGB(-WINDOW_WIDTH/2, (WINDOW_HEIGHT/3)+80, "Q pour se deplacer gauche", 0, 0, 0);
        showWordRGB(-WINDOW_WIDTH / 2, (WINDOW_HEIGHT / 3) + 60, "S pour se deplacer en arrière", 0, 0, 0);
        showWordRGB(-WINDOW_WIDTH/2, (WINDOW_HEIGHT/3)+40, "D pour se deplacer à droite", 0, 0, 0);
        showWordRGB(-WINDOW_WIDTH/2, (WINDOW_HEIGHT/3)+20, "Z pour se deplacer en avant", 0, 0, 0);
        showWordRGB(-WINDOW_WIDTH/2, (WINDOW_HEIGHT/3), "'Espace' pour selectionner une piece", 0, 0, 0);
        glColor3f(0, 0, 0);
        //  change la vue
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(fovy, screen_ratio, zNear, zoomOut * zFar);
        //    dessine la matrice
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(zoomOut * eyeX, zoomOut * eyeY, zoomOut * eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

        //   dessine le plateau
        if(board_rotating) doRotationBoard(chess->getTurnColor());
        GLfloat ambient_model[] = { 0.5, 0.5, 0.5, 1.0 };//bordure du plat

        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_model);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_diffusion);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffusion);

        glScalef(1.0f, 1.0f, -1.0f);

        glLightfv(GL_LIGHT0, GL_POSITION, position);

        glRotatef(rotation, 0, 0, 1);
        //dessine les elements
        drawChessBoard();

        drawBoardSquares();

        drawChessPieces();

        drawMoveToSquare();

        drawValidMoves();

		if(needPromote)
		{
			showWord(-200, WINDOW_HEIGHT/2-24, "Promote to: (R) Reine | (T) Tour | (F) Fou | (c) Cavalier");
		}
        else if(verify) showWord(-200, WINDOW_HEIGHT/2-24, "Voulez vous réessayer? OUI (O)  ou  NON (X)");
        else
        {
            if(check)
            {
                string s = chess->getTurnColor() == PieceColor::BLACK?"Piece noire" : "Piece blanche";
                showWord(-150, WINDOW_HEIGHT/2-24, s+" CHECKED!");
            }
            if(checkMate)
            {
                string s = chess->getTurnColor() == PieceColor::BLACK?"Joueur blanc" : "Joueur noir";
                showWord(-100, WINDOW_HEIGHT/2-24, "CHECK MATE!");
                showWord(-140, WINDOW_HEIGHT/2-50, s+" Gagne!");
                showWord(-150, -WINDOW_HEIGHT/2+50, "Tu veux jouer de nouveau?");
                showWord(-120, -WINDOW_HEIGHT/2+25, "Oui (O)  ou  Non (X)");
                glColor3f(0.545, 0.271, 0.075);
            }
        }
       
    }
    else
    {
        showWord(-150, 0, "- - Appuyez sur N Pour jouer - -");
    }
	if(closeGame)glutExit();

    glutSwapBuffers();

    glutPostRedisplay();
}

void reshapeFunction(int width, int height)
{
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    screen_ratio = (GLdouble) width / (GLdouble) height;
}

//  Commande avec les touches directionnel + scroll
void zoom(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_UP:
        case GLUT_KEY_UP:
            zoomOut += 0.1;
            break;
        case GLUT_DOWN:
        case GLUT_KEY_DOWN:
            zoomOut -= 0.1;
            break;
        case GLUT_KEY_LEFT:
            ang += 5;
            break;
        case GLUT_KEY_RIGHT:
            ang -= 5;
            break;
        default: break;
    }
}

//  Commande avec les touches du clavier
void keyFunction(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'z':
        case 'Z':
            if(!needPromote && !checkMate && !verify && inGame && !board_rotating) key_Z_pressed(chess->getTurnColor());
            break;
        case 'q':
        case 'Q':
            if(!needPromote && !checkMate && !verify && inGame && !board_rotating) key_Q_pressed(chess->getTurnColor());
            break;
        case 's':
        case 'S':
            if(!needPromote && !checkMate && !verify && inGame && !board_rotating) key_S_pressed(chess->getTurnColor());
            break;
        case 'd':
        case 'D':
            if(!needPromote && !checkMate && !verify && inGame && !board_rotating) key_D_pressed(chess->getTurnColor());
            break;
        case GLUT_LEFT_BUTTON:
        case ' ':
            if(!needPromote && !checkMate && !verify && inGame && !board_rotating)
            {
                if(selected)
                {
                    if(chess->move(selectedRow, selectedCol, moveToRow, moveToCol))
                    {
						Piece* movedPiece = chess->getPiece(moveToRow, moveToCol);
						if(movedPiece->getType() == PieceType::PAWN &&
							((movedPiece->getColor() == PieceColor::BLACK && moveToRow == chess->getBoard()->MIN_ROW_INDEX)
							|| moveToRow == chess->getBoard()->MAX_ROW_INDEX))
						{
							needPromote = true;
						}
						if(needPromote) break;
                        endOfTurn();
                    }
                    selected = false;
                }
                else if(chess->isSquareOccupied(selectedRow, selectedCol) && chess->getPieceColor(selectedRow, selectedCol) == chess->getTurnColor())
                {
                    selected = !selected;
                    if(selected)
                    {
                        moveToRow = selectedRow;
                        moveToCol = selectedCol;
                    }
                }
            }
            break;
        case 'n':
        case 'N':
            if(!inGame)newGame();
            else verify = true;
            break;
        case 'o': case 'O':
            if(checkMate || verify) {delete chess; newGame(); verify = false;}
            break;
        case 'x': case 'X':
			if(checkMate) { closeGame = true; delete chess;}
            if(verify) {verify = false;}
            break;
		case 'r': case 'R':
			if(needPromote)
			{
				chess->promote(moveToRow, moveToCol, PieceType::QUEEN);
				endOfTurn();
				break;
			}
			else break;
		case 't': case 'T':
			if(needPromote)
			{
				chess->promote(moveToRow, moveToCol, PieceType::ROOK);
				endOfTurn();
				break;
			}
			else break;
		case 'f': case 'F':
			if(needPromote)
			{
				chess->promote(moveToRow, moveToCol, PieceType::BISHOP);
				endOfTurn();
				break;
			}
			else break;
		case 'C': case 'c':
			if(needPromote)
			{
				chess->promote(moveToRow, moveToCol, PieceType::KNIGHT);
				endOfTurn();
				break;
			}
			else break;

		default: break;
    }
}

void initialize()
{
    // 0.2f, 0.6f, 0.5f, 1.0f couleur de fond
    glClearColor(0.2f, 0.2f, 0.2f, 0.1f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}

void newGame()
{
    chess = new Game();
    selectedRow = 1; selectedCol = 1;
    moveToRow = 1; moveToCol = 1;
    selected = false;
    board_rotating = true;
    rotation = 0;
    inGame = true;
    check = false;
    checkMate = false;
    updateTurn(chess->getTurnColor());
}


int main(int argc, char *argv[])
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
    glutCreateWindow("Chess");

    initialize();
    glutDisplayFunc(displayFunction);
    glutReshapeFunc(reshapeFunction);
    glutKeyboardFunc(keyFunction);
    glutSpecialFunc(zoom);
    glutMainLoop();
    return 0;
}
