/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaurice <jmaurice@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/18 15:20:44 by jmaurice          #+#    #+#             */
/*   Updated: 2014/01/19 18:42:41 by jmaurice         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
program = block "." . 										// un prog est un bloc suivi d'un point
 															// [] = 0 ou 1, {} = 0 ou n
 block =													// un bloc est un ens de
     ["const" ident "=" number {"," ident "=" number} ";"]	// avec n const nom = nb, repetee n fois
     ["var" ident {"," ident} ";"]							// n var nom repetes n fois
     {"procedure" ident ";" block ";"} statement .			// [n procedure nom ; block ;] obligatoirement suivi d'1 statement .
 
 statement =												// 1 statement
     ident ":=" expression									// nom := expression
     | "call" ident											// ou call nom
     | "begin" statement ";" {statement ";"} "end"			// ou begin statement ; [statement ;] end
     | "if" condition "then" statement						// ou if condition then statement
     | "while" condition "do" statement .					// ou while condition do statement .
 
 condition =												// 1 condition
     "odd" expression										// odd expression
     | expression ("="|"#"|"<"|"<="|">"|">=") expression .	// ou expression signe_op expression .
 
 expression = ["+"|"-"] term {("+"|"-") term} .				// 1 expression : + ou - term rep n fois .
 
 term = factor {("*"|"/") factor} .							// 1 term = factor rep n fois .
 
 factor =													// 1 factor
     ident													// nom
     | number												// ou nb
     | "(" expression ")" .									// (expression) .
*/

typedef enum {ident, number, lparen, rparen, times, slash, plus, 					// ident!, number!, ( ) * / +
			  minus, eql, neq, lss, leq, gtr, geq, callsym, beginsym, semicolon,	// - == != < <= > >= call begin ;
			  endsym, ifsym, whilesym, becomes, thensym, dosym, constsym, comma,	// end if while := then do const ,
			  varsym, procsym, period, oddsym} e_symbol;							// var procedure . odd

e_symbol sym;

void getsym(void);
void error(const char msg[]);
void expression(void);
 
int accept(e_symbol s) {
    if (sym == s) {
        getsym();
        return 1;
    }
    return 0;
}
 
int expect(e_symbol s) {
    if (accept(s))
        return 1;
    error("expect: unexpected symbol");
    return 0;
}
 
void factor(void) {
    if (accept(ident)) {
        ;
    } else if (accept(number)) {
        ;
    } else if (accept(lparen)) {
        expression();
        expect(rparen);
    } else {
        error("factor: syntax error");
        getsym();
    }
}
 
void term(void) {
    factor();
    while (sym == times || sym == slash) {
        getsym();
        factor();
    }
}
 
void expression(void) {
    if (sym == plus || sym == minus)
        getsym();
    term();
    while (sym == plus || sym == minus) {
        getsym();
        term();
    }
}
 
void condition(void) {
    if (accept(oddsym)) {
        expression();
    } 
	else {
        expression();
        if (sym == eql || sym == neq || sym == lss || sym == leq || sym == gtr || sym == geq) {
            getsym();
            expression();
        } 
		else {
            error("condition: invalid operator");
            getsym();
        }
    }
}
 
void statement(void) {
    if (accept(ident)) {
        expect(becomes);
        expression();
    } 
	else 
		if (accept(callsym)) {
        	expect(ident);
		} 
		else 
			if (accept(beginsym)) {
				do {
					statement();
				} while (accept(semicolon));
				expect(endsym);
			}
			else
				if (accept(ifsym)) {
					condition();
					expect(thensym);
					statement();
				}
				else
					if (accept(whilesym)) {
						condition();
						expect(dosym);
						statement();
					}
					else {
						error("statement: syntax error");
						getsym();
					}
}
 
void block(void) {
    if (accept(constsym)) { 	// si var
        do {
            expect(ident);
            expect(eql);
            expect(number);
        } while (accept(comma));// cont tt que virgules
        expect(semicolon);		// jq ; fin ligne
    }
    if (accept(varsym)) {		// idem var au-dessus
        do {
            expect(ident);
        } while (accept(comma));
        expect(semicolon);
    }
    while (accept(procsym)) {	// procedure
        expect(ident);
        expect(semicolon);
        block();				// recursion pr blocs (cf fonctions)
        expect(semicolon);
    }
    statement();
}
 
int		main(void) {
    getsym();
    block();
    expect(period);
}
