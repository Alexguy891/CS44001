// Author:      Alex Ely
// Date:        11/02/2022
// Project:     Lab 9
// Description: Square painting using bridge design

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill{
public:
    Fill(char borderChar, char fillChar): 
        borderChar_(borderChar),
        fillChar_(fillChar){}
    virtual char getBorder()=0;
    virtual char getInternal()=0;
    virtual ~Fill() {}
protected:
    char fillChar_;
    char borderChar_;
};

// concrete body
class Hollow: public Fill{
public:
    Hollow(char borderChar):Fill(borderChar, ' '){}
    char getBorder() override {return borderChar_;}
    char getInternal() override {return ' ';}
    ~Hollow() override {}
};


// another concrete body
class Filled: public Fill {
public:
   Filled(char borderChar):Fill(borderChar, borderChar){}
   char getBorder() override {return borderChar_;}
   char getInternal() override {return borderChar_;}
   ~Filled() override {}
};

class FullyFilled: public Fill {
public:
   FullyFilled(char borderChar, char fillChar):Fill(borderChar, fillChar){}
   char getBorder() override {return borderChar_;}
   char getInternal() override {return fillChar_;}
   ~FullyFilled() override {}
};

class RandomFilled: public Fill {
public:
   RandomFilled(char borderChar, char fillChar):Fill(borderChar, fillChar){}
   char getBorder() override {return rand() % 2 == 0 ? borderChar_ : fillChar_;}
   char getInternal() override {return rand() % 2 == 1 ? fillChar_ : borderChar_;}
   ~RandomFilled() override {}
};

// abstract handle
class Figure {
public:
   Figure(int size, Fill* fill): size_(size), fill_(fill){}
   virtual void draw() =0;
   virtual ~Figure(){}
protected:
   int size_;
   Fill *fill_;
};

// concrete handle
class Square: public Figure{
public:
   Square(int size, Fill* fill): Figure(size, fill){}
   void draw() override;

};

void Square::draw(){
   for(int i=0; i < size_; ++i){
      for(int j=0; j < size_; ++j)
	 if(i==0 || j==0 || i==size_-1 || j==size_-1 )
	    cout << fill_ -> getBorder();
	 else
	    cout << fill_ -> getInternal();
      cout << endl;
   }
}

int main(){

   
    Fill* hollowPaintQ = new Hollow('Q');
    Fill* filledPaintStar = new Filled('*');
    Fill* fullyFilled = new FullyFilled('=','S');
    Fill* randomFilled = new RandomFilled('X','A');
   
    Figure *smallBox = new Square(5, hollowPaintQ);
    Figure *bigBox = new Square(15, filledPaintStar);
    Figure *mediumBox = new Square(10, fullyFilled);
    Figure *giantBox = new Square(25, randomFilled);

    smallBox->draw();
    cout << endl;
    bigBox -> draw();
    cout << endl;
    mediumBox->draw();
    cout << endl;
    giantBox->draw();
    cout << endl;
}