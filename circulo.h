#ifndef CIRCULO_H
#define CIRCULO_H

/**
 * @file circulo.h
 * @brief Definições do TAD Círculo (formato em SVG).
 * 
 * @details
 * O arquivo circulo.h declara a interface de um TAD, que representa um círculo
 * em um plano bidimensional. Cada círculo possui um identificador, coordenadas (x,y),
 * raio e cores de preenchimento e borda representadas como strings.
 */ 
 
 typedef void* CIRCULO;
 
/**
 * @param id identificador.
 * @param x coordenada x do círculo.
 * @param y coordenada y do círculo.
 * @param raio raio do círculo.
 * @param corP cor de preenchimento do círculo.
 * @param corB cor da borda do círculo.
 * 
 * @return retorna um ponteiro para "CIRCULO".
 * 
 * 
*/


CIRCULO cria_circulo(int id, float x, float y, float raio, const char* corP, const char* corB);

/**
 * @brief Faz o ID do círculo.
 * 
 * @param c o círculo que vai possuir o ID.
 * @return O id da forma.  
 * 
*/

int getIDCirculo(CIRCULO c);

/**
 * @brief Faz o valor da coordenada X do círculo.
 * 
 * @param c O círculo que vai possuir a coordenada X.
 * @return A coordenada X da forma.  
 * 
*/

float getXCirculo(CIRCULO c);

/**
 * @brief Faz o valor da coordenada Y do círculo.
 * 
 * @param c O circulo que vai possuir a coordenada Y.
 * @return A coordenada Y da forma.  
 * 
*/

float getYCirculo(CIRCULO c);

/**
 * @brief Faz o valor do raio do círculo.
 * 
 * @param c O circulo que vai possuir o valor do raio.
 * @return O raio da forma.  
 * 
*/

float getRaioCirculo(CIRCULO c);

/**
 * @brief Faz a cor de preenchimento do círculo.
 * 
 * @param c O circulo que vai possuir a cor de preenchimento.
 * @return String da cor de preenchimento da forma.  
 * 
*/

char* getCorPCirculo(CIRCULO c);

/**
 * @brief Faz a cor da borda do círculo.
 * 
 * @param c O circulo que vai possuir a cor da borda.
 * @return String da cor da borda da forma.  
 * 
*/

char* getCorBCirculo(CIRCULO c);

/**
 * @brief Faz o calculo da área do círculo.
 * 
 * @param c A area do circulo.
 * @return O valor da área da forma.  
 * 
*/

float getAreaCirculo(CIRCULO c);

/**
 * @brief Define o ID do círculo.
 * 
 * @param c o círculo com o ID definido.
 * @param id Novo ID definido.
 */

void setIDCirculo(CIRCULO c, int id);

/**
 * @brief Define a coordenada X do círculo.
 * 
 * @param c o círculo com a coordenada X definido.
 * @param x Novo valor da coordenada X definido.
 */


void setXCirculo(CIRCULO c, float x);

/**
 * @brief Define a coordenada Y do círculo.
 * 
 * @param c o círculo com a coordenada Y definido.
 * @param y Novo valor da coordenada Y definido.
 */

void setYCirculo(CIRCULO c, float y);

/**
 * @brief Define o raio do círculo.
 * 
 * @param c o círculo com o raio definido.
 * @param raio Novo valor do raio definido.
 */

void setRaioCirculo(CIRCULO c, float raio);

/**
 * @brief Define a cor de preenchimento do círculo.
 * 
 * @param c o círculo com a cor de preencimento definido.
 * @param corP Novo valor para a cor de preenchimento definido.
 */

void setCorPCirculo(CIRCULO c, const char* corP);

/**
 * @brief Define a cor da borda do círculo.
 * 
 * @param c o círculo com a cor da borda definido.
 * @param corB Novo valor para a cor da borda definido.
 */

void setCorBCirculo(CIRCULO c, const char* corB);

/**
 * @brief Libera a memória alocada para o círculo.
 * @param c ponteiro do círculo a ser destruído.
 */
void destroiCirculo(CIRCULO c);

#endif