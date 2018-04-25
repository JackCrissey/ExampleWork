// File: Sally.cpp
//
// CMSC 341 Spring 2017 Project 2
//
// Implementation of member functions of Sally Forth interpreter
//

#include <iostream>
#include <string>
#include <list>
#include <stack>
#include <stdexcept>
#include <cstdlib>
using namespace std ;

#include "Sally.h"


// Basic Token constructor. Just assigns values.
//
Token::Token(TokenKind kind, int val, string txt) {
   m_kind = kind ;
   m_value = val ;
   m_text = txt ;
}


// Basic SymTabEntry constructor. Just assigns values.
//
SymTabEntry::SymTabEntry(TokenKind kind, int val, operation_t fptr) {
   m_kind = kind ;
   m_value = val ;
   m_dothis = fptr ;
}


// Constructor for Sally Forth interpreter.
// Adds built-in functions to the symbol table.
//
Sally::Sally(istream& input_stream) :
   istrm(input_stream)  // use member initializer to bind reference
{
   symtab["DUMP"]    =  SymTabEntry(KEYWORD,0,&doDUMP) ;
   symtab["+"]    =  SymTabEntry(KEYWORD,0,&doPlus) ;
   symtab["-"]    =  SymTabEntry(KEYWORD,0,&doMinus) ;
   symtab["*"]    =  SymTabEntry(KEYWORD,0,&doTimes) ;
   symtab["/"]    =  SymTabEntry(KEYWORD,0,&doDivide) ;
   symtab["%"]    =  SymTabEntry(KEYWORD,0,&doMod) ;
   symtab["NEG"]  =  SymTabEntry(KEYWORD,0,&doNEG) ;
    symtab["DUP"]  =  SymTabEntry(KEYWORD,0,&doDUP) ;
    symtab["DROP"]  =  SymTabEntry(KEYWORD,0,&doDROP) ;
    symtab["SWAP"]  =  SymTabEntry(KEYWORD,0,&doSWAP) ;
    symtab["ROT"]  =  SymTabEntry(KEYWORD,0,&doROT) ;
    symtab["SET"]  =  SymTabEntry(KEYWORD,0,&doSET) ;
    symtab["@"]  =  SymTabEntry(KEYWORD,0,&doFETCH) ;
    symtab["!"]  =  SymTabEntry(KEYWORD,0,&doStore) ;
    symtab["<"]  =  SymTabEntry(KEYWORD,0,&doGreater) ;
    symtab["<="]  =  SymTabEntry(KEYWORD,0,&doGreaterEqual) ;
    symtab["=="]  =  SymTabEntry(KEYWORD,0,&doEqual) ;
    symtab["!="]  =  SymTabEntry(KEYWORD,0,&doNotEqual) ;
    symtab[">="]  =  SymTabEntry(KEYWORD,0,&doLessEqual) ;
    symtab[">"]  =  SymTabEntry(KEYWORD,0,&doLess) ;
    symtab["AND"]  =  SymTabEntry(KEYWORD,0,&doAND) ;
    symtab["OR"]  =  SymTabEntry(KEYWORD,0,&doOR) ;
    symtab["NOT"]  =  SymTabEntry(KEYWORD,0,&doNOT) ;
    symtab["IFTHEN"]  =  SymTabEntry(KEYWORD,0,&doIfThen) ;
    symtab["ELSE"]  =  SymTabEntry(KEYWORD,0,&doElse) ;
    symtab["ENDIF"]  =  SymTabEntry(KEYWORD,0,&doEndIf) ;
    symtab["DO"]  =  SymTabEntry(KEYWORD,0,&doDo) ;
    symtab["UNTIL"]  =  SymTabEntry(KEYWORD,0,&doUntil) ;
   symtab["."]    =  SymTabEntry(KEYWORD,0,&doDot) ;
   symtab["SP"]   =  SymTabEntry(KEYWORD,0,&doSP) ;
   symtab["CR"]   =  SymTabEntry(KEYWORD,0,&doCR) ;
    counter = 0;
}


// This function should be called when tkBuffer is empty.
// It adds tokens to tkBuffer.
//
// This function returns when an empty line was entered 
// or if the end-of-file has been reached.
//
// This function returns false when the end-of-file was encountered.
// 
// Processing done by fillBuffer()
//   - detects and ignores comments.
//   - detects string literals and combines as 1 token
//   - detetcs base 10 numbers
// 
//
bool Sally::fillBuffer() {
   string line ;     // single line of input
   int pos ;         // current position in the line
   int len ;         // # of char in current token
   long int n ;      // int value of token
   char *endPtr ;    // used with strtol()


   while(true) {    // keep reading until empty line read or eof

      // get one line from standard in
      //
      getline(istrm, line) ;   

      // if "normal" empty line encountered, return to mainLoop
      //
      if ( line.empty() && !istrm.eof() ) {
         return true ;
      }

      // if eof encountered, return to mainLoop, but say no more
      // input available
      //
      if ( istrm.eof() )  {
     return false ;
      }


      // Process line read

       pos = 0;                      // start from the beginning
      // skip over initial spaces & tabs
      //
      while( line[pos] != '\0' && (line[pos] == ' ' || line[pos] == '\t') ) {
     pos++ ; 
      }

      // Keep going until end of line
      //
      while (line[pos] != '\0') {

         // is it a comment?? skip rest of line.
     //
         if (line[pos] == '/' && line[pos+1] == '/') break ;

         // is it a string literal? 
     //
         if (line[pos] == '.' && line[pos+1] == '"') {

        pos += 2 ;  // skip over the ."
        len = 0 ;   // track length of literal

            // look for matching quote or end of line
        //
        while(line[pos+len] != '\0' && line[pos+len] != '"') {
           len++ ;
        }

            // make new string with characters from
        // line[pos] to line[pos+len-1]
        string literal(line,pos,len) ;  // copy from pos for len chars

            // Add to token list
        //
        tkBuffer.push_back( Token(STRING,0,literal) ) ;  

            // Different update if end reached or " found
            //
        if (line[pos+len] == '\0') {
           pos = pos + len ;
        } else {
           pos = pos + len + 1 ;
        }

     } else {  // otherwise "normal" token

        len = 0 ;  // track length of token

            // line[pos] should be an non-white space character
        // look for end of line or space or tab
        //
        while(line[pos+len] != '\0' && line[pos+len] != ' ' && line[pos+len] != '\t') {
           len++ ;
        }

        string literal(line,pos,len) ;   // copy form pos for len chars
        pos = pos + len ;

            // Try to convert to a number
        //
            n = strtol(literal.c_str(), &endPtr, 10) ;

            if (*endPtr == '\0') {
           tkBuffer.push_back( Token(INTEGER,n,literal) ) ;
        } else {
           tkBuffer.push_back( Token(UNKNOWN,0,literal) ) ;
        }
     }

     // skip over trailing spaces & tabs
     //
     while( line[pos] != '\0' && (line[pos] == ' ' || line[pos] == '\t') ) {
        pos++ ; 
     }

      }
   }
}



// Return next token from tkBuffer.
// Call fillBuffer() if needed.
// Checks for end-of-file and throws exception 
//
Token Sally::nextToken() {
      Token tk ;
      bool more = true ;
      if(counter != 0)       // This if statement is only used for the Do Until loop
      {                      // and uses an looped que to store the tokens.
          tk = save.front(); // Saves the value on the front of the que
          save.pop_front();  //Pops the value off the front
          save.push_back(tk);//Saves that value on the back of the que
          return tk;         //Returns the top value
      }
      while(more && tkBuffer.empty() ) {
         more = fillBuffer() ;
      }

      if ( !more && tkBuffer.empty() ) {
         throw EOProgram("End of Program") ;
      }

      tk = tkBuffer.front() ;
      tkBuffer.pop_front() ;
      return tk ;
}


// The main interpreter loop of the Sally Forth interpreter.
// It gets a token and either push the token onto the parameter
// stack or looks for it in the symbol table.
//
//
void Sally::mainLoop() {

   Token tk ;
   map<string,SymTabEntry>::iterator it ;

   try {
      while( 1 ) {
     tk = nextToken() ;

     if (tk.m_kind == INTEGER || tk.m_kind == STRING) {

            // if INTEGER or STRING just push onto stack
        params.push(tk) ;

     } else { 
        it = symtab.find(tk.m_text) ;
        
        if ( it == symtab.end() )  {   // not in symtab

           params.push(tk) ;

        } else if (it->second.m_kind == KEYWORD)  {

           // invoke the function for this operation
           //
           it->second.m_dothis(this) ;   
           
        } else if (it->second.m_kind == VARIABLE) {

               // variables are pushed as tokens
           //
           tk.m_kind = VARIABLE ;
           params.push(tk) ;

        } else {

               // default action
           //
           params.push(tk) ;

        }
     }
      }

   } catch (EOProgram& e) {

      cerr << "End of Program\n" ;
      if ( params.size() == 0 ) {
         cerr << "Parameter stack empty.\n" ;
      } else {
         cerr << "Parameter stack has " << params.size() << " token(s).\n" ;
      }

   } catch (out_of_range& e) {

      cerr << "Parameter stack underflow??\n" ;

   } catch (...) {

      cerr << "Unexpected exception caught\n" ;

   }
}

// -------------------------------------------------------


void Sally::doPlus(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for +.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value + p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doMinus(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for -.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value - p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doTimes(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for *.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value * p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doDivide(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for /.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value / p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doMod(Sally *Sptr) {
   Token p1, p2 ;

   if ( Sptr->params.size() < 2 ) {
      throw out_of_range("Need two parameters for %.") ;
   }
   p1 = Sptr->params.top() ;
   Sptr->params.pop() ;
   p2 = Sptr->params.top() ;
   Sptr->params.pop() ;
   int answer = p2.m_value % p1.m_value ;
   Sptr->params.push( Token(INTEGER, answer, "") ) ;
}


void Sally::doNEG(Sally *Sptr) {
   Token p ;

   if ( Sptr->params.size() < 1 ) {
      throw out_of_range("Need one parameter for NEG.") ;
   }
   p = Sptr->params.top() ;
   Sptr->params.pop() ;
   Sptr->params.push( Token(INTEGER, -p.m_value, "") ) ;
}

//Duplicates the top value and pushes it back onto the top of the stack
void Sally::doDUP(Sally *Sptr)
{
    Token p1;
    if ( Sptr->params.size() < 1 )
    {
        throw out_of_range("Need one parameter for DUP.") ;
    }
    p1 =Sptr->params.top(); //Copies the top value to a token
    Sptr->params.push(p1);  //Pushes the duplicate token to the top if the stack
}

//Deletes the top token
void Sally::doDROP(Sally *Sptr)
{
    if ( Sptr->params.size() < 1 ) {
        throw out_of_range("Need one parameter for DROP.") ;
    }
    Sptr->params.pop();//Pops the top token off
}

//Swaps the top two Tokens on the stack
void Sally::doSWAP(Sally *Sptr)
{
    Token p1,p2;
    if ( Sptr->params.size() < 2 ) {
        throw out_of_range("Need two parameters for SWAP.") ;
    }
    p1 = Sptr->params.top();
    Sptr->params.pop();      //Saves and pops the first token on the stack
    p2 = Sptr->params.top();
    Sptr->params.pop();      //Saves and pops the second token on the stack
    Sptr->params.push(p1);   //Pushes the first token onto the stack
    Sptr->params.push(p2);   //Pushes the second token onto the stack
}

/*Rotates the top 3 elements moving the Third token to the Top (or First) spot 
 in the stack and moves the First element and Second element of the stack down
 to the Second and Third spots on the stack respectively.*/
void Sally::doROT(Sally *Sptr)
{
    Token p1,p2,p3;
    if ( Sptr->params.size() < 3 ) {
        throw out_of_range("Need three parameters for ROT.") ;
    }
    p1 = Sptr->params.top();
    Sptr->params.pop();
    p2 = Sptr->params.top();
    Sptr->params.pop();
    p3 = Sptr->params.top();
    Sptr->params.pop();      //Pops and saves the first 3 token of the Stack
    Sptr->params.push(p2);   //Pushes the second token to the bottom
    Sptr->params.push(p1);   //Pushes the first tokem to the second spot
    Sptr->params.push(p3);   //Pushes the third token to the top
}

/*Creates a new Variable for the Symbol table and saves it as a variable with a 
 specific value*/
void Sally::doSET(Sally *Sptr)
{
    Token p1, p2;
    if ( Sptr->params.size() < 2 ) {
        throw out_of_range("Need two parameters for SET.") ;
    }
    p1 = Sptr->params.top();
    Sptr->params.pop();
    p2 = Sptr->params.top();
    Sptr->params.pop();       //Pops and saves the top 2 Tokens on the Stack
    if (Sptr->symtab.count(p1.m_text) > 0)  //Checks to see if the symbol table already has a variable of the name entered
    {
        throw out_of_range("Variable already exists.");
    }
    //Creates a new symbol table entry
    SymTabEntry temp = SymTabEntry(VARIABLE, p2.m_value);
    //Saves the new entry using the variable name that it took from the text file.
    Sptr->symtab.insert(pair<string, SymTabEntry>(p1.m_text,temp));
}

//Fetches the value for the requested variable.
void Sally::doFETCH(Sally *Sptr)
{
    if ( Sptr->params.size() < 1 ) {
        throw out_of_range("Need two parameters for Fetch.") ;
    }
    Token p1;
    p1 = Sptr->params.top();
    Sptr->params.pop();     //Saves and Pops the top token
    if (Sptr->symtab.count(p1.m_text) == 0)
    {
        throw out_of_range("Variable does not exist.");
    }
    int x = Sptr->symtab[p1.m_text].m_value;//Fetches the value from the Variable
    Token temp =  Token(INTEGER, x);        //Creates an Integer Token for value
    Sptr->params.push(temp);       //Pushes the Token with that value onto the stack
}

/*Stores the value that it reads form the Token in the stack to the variable
 that was also in the stack.*/
void Sally::doStore(Sally *Sptr)
{
    if ( Sptr->params.size() < 2 ) {
        throw out_of_range("Need two parameters for Store.") ;
    }
    Token p1;
    p1 =Sptr->params.top();
    Sptr->params.pop();
    Token p2;
    p2 =Sptr->params.top();
    Sptr->params.pop();     //Pops and Saves the value and the variable
    if (Sptr->symtab.count(p1.m_text) == 0)
    {
        throw out_of_range("Variable does not exist.");
    }
    Sptr->symtab[p1.m_text].m_value = p2.m_value; //Stores the value in the variable
}

/*If the value of of the first token is greater then the value of the second token
 then true is returned else false is returned.*/
void Sally::doGreater(Sally *Sptr)
{
    if ( Sptr->params.size() < 2 ) {
        throw out_of_range("Need two parameters for Greater than.") ;
    }
    Token p1;
    p1 =Sptr->params.top();
    Sptr->params.pop();
    Token p2;
    p2 =Sptr->params.top();
    Sptr->params.pop();         //Pops and saves the two integers
    if(p1.m_value>p2.m_value)   //Checks to see if p1 is greater than p2
    {
        Token temp = Token(INTEGER,1);  //creates a true integer
        Sptr->params.push(temp);        //pushes it on the stack
    }
    else
    {
        Token temp = Token(INTEGER,0);  //creates a false integer
        Sptr->params.push(temp);        //pushes it on the stack
    }
}

/*If the value of of the first token is greater then or equal to the value of the 
 second token then true is returned else false is returned.*/
void Sally::doGreaterEqual(Sally *Sptr)
{
    if ( Sptr->params.size() < 2 ) {
        throw out_of_range("Need two parameters for Greater or Equal too.") ;
    }
    Token p1;
    p1 =Sptr->params.top();
    Sptr->params.pop();
    Token p2;
    p2 =Sptr->params.top();
    Sptr->params.pop();

    if(p1.m_value>=p2.m_value)  //Checks to see if p1 is greater than or equal to p2
    {
        Token temp = Token(INTEGER,1);  //creates a true integer
        Sptr->params.push(temp);        //pushes it on the stack
    }
    else
    {
        Token temp = Token(INTEGER,0);  //creates a false integer
        Sptr->params.push(temp);        //pushes it on the stack
    }

}

/*If the value of of the first token is equal to the value of the
 second token then true is returned else false is returned.*/
void Sally::doEqual(Sally *Sptr)
{
    if ( Sptr->params.size() < 2 ) {
        throw out_of_range("Need two parameters for Equal to0.") ;
    }
    Token p1;
    p1 =Sptr->params.top();
    Sptr->params.pop();
    Token p2;
    p2 =Sptr->params.top();
    Sptr->params.pop();

    if(p1.m_value==p2.m_value)  //Checks to see if p1 is equal to p2
    {
        Token temp = Token(INTEGER,1);  //creates a true integer
        Sptr->params.push(temp);        //pushes it on the stack
    }
    else
    {
        Token temp = Token(INTEGER,0);  //creates a false integer
        Sptr->params.push(temp);        //pushes it on the stack
    }
}

/*If the value of of the first token is not equal to the value of the
 second token then true is returned else false is returned.*/
void Sally::doNotEqual(Sally *Sptr)
{
    if ( Sptr->params.size() < 2 ) {
        throw out_of_range("Need two parameters for not equal too.") ;
    }
    Token p1;
    p1 =Sptr->params.top();
    Sptr->params.pop();
    Token p2;
    p2 =Sptr->params.top();
    Sptr->params.pop();

    if(p1.m_value!=p2.m_value)  //Checks to see if p1 is not equal to p2
    {
        Token temp = Token(INTEGER,1);  //creates a true integer
        Sptr->params.push(temp);        //pushes it on the stack
    }
    else
    {
        Token temp = Token(INTEGER,0);  //creates a false integer
        Sptr->params.push(temp);        //pushes it on the stack
    }

}

/*If the value of of the first token is less then or equal to the value of the
 second token then true is returned else false is returned.*/
void Sally::doLessEqual(Sally *Sptr)
{
    if ( Sptr->params.size() < 2 ) {
        throw out_of_range("Need two parameters for less than or equal too.") ;
    }
    Token p1;
    p1 =Sptr->params.top();
    Sptr->params.pop();
    Token p2;
    p2 =Sptr->params.top();
    Sptr->params.pop();

    if(p1.m_value<=p2.m_value)  //Checks to see if p1 is less than or equal to p2
    {
        Token temp = Token(INTEGER,1);  //creates a true integer
        Sptr->params.push(temp);        //pushes it on the stack
    }
    else
    {
        Token temp = Token(INTEGER,0);  //creates a false integer
        Sptr->params.push(temp);        //pushes it on the stack
    }
}

/*If the value of of the first token is less then the value of the
 second token then true is returned else false is returned.*/
void Sally::doLess(Sally *Sptr)
{
    if ( Sptr->params.size() < 2 ) {
        throw out_of_range("Need two parameters for less than.") ;
    }
    Token p1;
    p1 =Sptr->params.top();
    Sptr->params.pop();
    Token p2;
    p2 =Sptr->params.top();
    Sptr->params.pop();

    if(p1.m_value<p2.m_value)   //Checks to see if p1 is less than to p2
    {
        Token temp = Token(INTEGER,1);  //creates a true integer
        Sptr->params.push(temp);        //pushes it on the stack
    }
    else
    {
        Token temp = Token(INTEGER,0);  //creates a false integer
        Sptr->params.push(temp);        //pushes it on the stack
    }
}

/*If the top two values popped off the stack are true then the fuction returns true
 else it returns false*/
void Sally::doAND(Sally *Sptr)
{
    if ( Sptr->params.size() < 2 ) {
        throw out_of_range("Need two parameters for AND.") ;
    }
    Token p1;
    p1 =Sptr->params.top();
    Sptr->params.pop();
    Token p2;
    p2 =Sptr->params.top();
    Sptr->params.pop();
    //If both tokens have true values then return true.
    if(p1.m_value != 0 && p2.m_value != 0)
    {
        Token temp = Token(INTEGER,1);  //creates a true integer
        Sptr->params.push(temp);        //pushes it on the stack
    }
    else
    {
        Token temp = Token(INTEGER,0);  //creates a false integer
        Sptr->params.push(temp);        //pushes it on the stack
    }
}

/*If one of the two values that is popped off the stack are true then the fuction
 returns true else the fuction returns false.*/
void Sally::doOR(Sally *Sptr)
{
    if ( Sptr->params.size() < 2 ) {
        throw out_of_range("Need two parameters for Or.") ;
    }
    Token p1;
    p1 =Sptr->params.top();
    Sptr->params.pop();
    Token p2;
    p2 =Sptr->params.top();
    Sptr->params.pop();
    //If either token has a true value then true is returned
    if(p1.m_value != 0 || p2.m_value != 0)
    {
        Token temp = Token(INTEGER,1);  //creates a true integer
        Sptr->params.push(temp);        //pushes it on the stack
    }
    else
    {
        Token temp = Token(INTEGER,0);  //creates a false integer
        Sptr->params.push(temp);        //pushes it on the stack
    }
}
/*If the value on the top of the stack is false then true is pushed back onto
 the top. If the value on the top of the stack is true then false is pushed back onto
 the top.*/
void Sally::doNOT(Sally *Sptr)
{
    if ( Sptr->params.size() < 1 ) {
        throw out_of_range("Need one parameters for Not.") ;
    }
    Token p1;
    p1 =Sptr->params.top();
    Sptr->params.pop();
    if(p1.m_value != 0)
    {
        Token temp = Token(INTEGER,0);  //creates a false integer
        Sptr->params.push(temp);        //pushes it on the stack
    }
    else if(p1.m_value == 0)
    {
        Token temp = Token(INTEGER,1);  //creates a true integer
        Sptr->params.push(temp);        //pushes it on the stack
    }
}

/*When the program sees an IfThen the program pops the top value and continues on
 with the program, but if it sees a false IFTHEN then the program will start
 searching the program to find an IFTHEN token. When it does it adds a value of 2
 to the stack this lets the program know it found an IFTHEN. When it encounters an
 ENDIF token it will pop one of the 2 values off the stack. When their are know 2 
 Tokens on the stack the program knows that it has reached the right else statement
 where it will then execute the else.*/
void Sally::doIfThen(Sally *Sptr)
{
    if ( Sptr->params.size() < 1 ) {
        throw out_of_range("Need one parameters for IfThen.") ;
    }
    Token p1;
    p1 =Sptr->params.top();
    Sptr->params.pop();
    //If the IFTHEN statement is true then the program will add 3 onto the stack so
    //that the program can use it to find the end of nested statements later on.
    if(p1.m_value != 0)
    {
        Sptr -> params.push(Token(INTEGER, 3));
    }
    if(p1.m_value == 0)//If the IFTHEN statement is false
    {
        //store the next token value in a string
        string good = Sptr->nextToken().m_text;
        Sptr->params.push(Token(INTEGER, 0));//Push a place hold on the stack
        while(good != "ELSE")//While the token doesn't equal else
        {
            if(good == "IFTHEN")//Finds the first IFTHEN
            {
                Token temp = Token(INTEGER, 2);//pushes the 2 integer on the stack
                Sptr->params.push(temp);
            }
            int x = 0;//sets the count to zero
            good = Sptr->nextToken().m_text;
            while(Sptr->params.top().m_value == 2)
            {
                if(good == "IFTHEN" && x != 0)//if an IFTHEN is found add 2 to the stack
                {
                    Token temp = Token(INTEGER, 2);
                    Sptr->params.push(temp);
                }
                if(good == "ENDIF")//if an ENDIF is found pop 2 off the stack
                {
                    Sptr->params.pop();
                }
                good = Sptr->nextToken().m_text;
                x++;
            }
        }
        Sptr->params.pop();
    }
}
//This is just here to be called.
void Sally::doElse(Sally *Sptr)
{
   
}

/*Once ENDIF is called the program keeps moving through the tokens until it has
 reached the end of the loop. It does this by counting the IFTHEN tokens by adding a
 value of 3 to the stack. If ENDIF is encountered then it pops the 3 off the stack.
 When their are no more values left it end the loop because it is at the end of the
 IFTHEN statements.*/
void Sally::doEndIf(Sally *Sptr)
{
    string good = Sptr->nextToken().m_text;
    while(Sptr->params.top().m_value == 3)
    {
        if(good == "IFTHEN")//if an IFTHEN is found add 3 to the stack
        {
            Token temp = Token(INTEGER, 3);
            Sptr->params.push(temp);
        }
        if(good == "ENDIF")//if an ENDIF is found pop 3 off the stack
        {
            Sptr->params.pop();
        }
            good = Sptr->nextToken().m_text;
    }
}

/*creates a new que and saves all of the tokens in the do loop into that que. The 
 que will be used as a circular que that will move the popped token to the back of
 the que.*/
void Sally::doDo(Sally *Sptr)
{
        Token good = Sptr->nextToken();
        while(good.m_text != "UNTIL")   //keeps the loop going till the last token of the do loop;
        {
            Sptr->save.push_back(good);
            good = Sptr->nextToken();
        }
        Token temp = Token(UNKNOWN,0,"UNTIL");
        Sptr->save.push_back(temp);     //Pushes until onto the que
        Sptr->counter++;    //Makes it so that the nextToken class iterates through the que.
}
/*Pops the value off the loop if it is true then it ends the loop*/
void Sally::doUntil(Sally *Sptr)
{
    if ( Sptr->params.size() < 1 ) {
        throw out_of_range("Need one parameters for Until.") ;
    }
    Token p1;
    p1 =Sptr->params.top();
    Sptr->params.pop();
    if(p1.m_value != 0)
    {
        Sptr->save.clear();//clears the que
        Sptr->counter = 0;//makes the nextToken class iterate nomally
    }
}

void Sally::doDot(Sally *Sptr) {

   Token p;
   if ( Sptr->params.size() < 1 ) {
      throw out_of_range("Need one parameter for .") ;
   }

   p = Sptr->params.top() ;
   Sptr->params.pop() ;

   if (p.m_kind == INTEGER) {
      cout << p.m_value ;
   } else {
      cout << p.m_text ;
   }
}


void Sally::doSP(Sally *Sptr) {
   cout << " " ;
}


void Sally::doCR(Sally *Sptr) {
   cout << endl ;
}

void Sally::doDUMP(Sally *Sptr) {
    
} 
