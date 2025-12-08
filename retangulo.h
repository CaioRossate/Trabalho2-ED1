#ifndef RETANGULO_H
#define RETANGULO_H

/**
 * @file retangulo.h
 * @brief Definições do TAD Retângulo (formato em SVG).
 * 
 * @details
 * O arquivo retangulo.h declara a interface de um TAD que
 * representa um retângulo em um plano bidimensional. Cada retângulo possui
 * um identificador, coordenadas (x,y) do canto superior esquerdo, largura,
 * altura e cores de preenchimento e borda representadas como strings.
 */

 typedef void* RETANGULO;

 /**
 * @param id identificador.
 * @param x coordenada x do retângulo.
 * @param y coordenada y do retângulo.
 * @param largura largura do retângulo.
 * @param altura altura do retângulo.
 * @param corP cor de preenchimento do retângulo.
 * @param corB cor da borda do retângulo.
 *
 * @return retorna um ponteiro para "RETANGULO".
 * 
 */ 
 RETANGULO cria_retangulo(int id, float x, float y, float largura, float altura, const char* corP, const char* corB);

/**
 * @brief Faz o ID do retangulo.
 * 
 * @param r o retângulo que vai possuir o ID.
 * @return O id da forma.
 */
int getIDRetangulo(RETANGULO r);

/**
 * @brief Faz o valor da coordenada X do retângulo.
 *
 * @param r o retângulo que vai possuir a coordenada X.
 * @return A coordenada X da forma.
 */
float getXRetangulo(RETANGULO r);

/**
 * @brief Faz o valor da coordenada Y do retângulo.
 *
 * @param r o retângulo que vai possuir a coordenada Y.
 * @return A coordenada Y da forma.
 */
float getYRetangulo(RETANGULO r);

/**
 * @brief Faz o valor da largura do retângulo.
 *
 * @param r o retângulo que vai possuir o valor da largura.
 * @return A largura da forma.
 */
float getLarguraRetangulo(RETANGULO r);

/**
 * @brief Faz o valor da altura do retângulo.
 *
 * @param r o retângulo que vai possuir o valor da altura.
 * @return A altura da forma.
 */
float getAlturaRetangulo(RETANGULO r);

/**
 * @brief Faz a cor de preenchimento do retângulo.
 *
 * @param r o retângulo que vai possuir a cor de preenchimento.
 * @return String da cor de preenchimento da forma.
 */
char* getCorPRetangulo(RETANGULO r);

/**
 * @brief Faz a cor da borda do retângulo.
 *
 * @param r o retângulo que vai possuir a cor de borda.
 * @return String da cor de borda da forma.
 */
char* getCorBRetangulo(RETANGULO r);

/**
 * @brief Faz o calculo da área do retângulo.
 *
 * @param r A area do retangulo.
 * @return O valor da área da forma.
 */
float getAreaRetangulo(RETANGULO r);

/**
 * @brief Define o ID do retângulo.
 *
 * @param r o retângulo com o ID definido.
 * @param id Novo ID definido.
 */
void setIDRetangulo(RETANGULO r, int id);

/**
 * @brief Define a coordenada X do retângulo.
 *
 * @param r o retângulo com o X definido.
 * @param x Novo valor da coordenada X definido.
 */
void setXRetangulo(RETANGULO r, float x);

/**
 * @brief Define a coordenada Y do retângulo.
 *
 * @param r o retângulo com o Y definido.
 * @param y Novo valor da coordenada Y definido.
 */
void setYRetangulo(RETANGULO r, float y);

/**
 * @brief Define a largura do retângulo.
 *
 * @param r o retângulo com a largura definido.
 * @param largura Novo valor da largura definido.
 */
void setLarguraRetangulo(RETANGULO r, float largura);

/**
 * @brief Define a altura do retângulo.
 *
 * @param r o retângulo com a altura definido.
 * @param altura Novo valor da altura definido.
 */
void setAlturaRetangulo(RETANGULO r, float altura);

/**
 * @brief Define a cor de preenchimento do retângulo.
 *
 * @param r o retângulo com a cor de preenchimento definido.
 * @param corP Nova string da cor de preenchimento definido.
 */
void setCorPRetangulo(RETANGULO r, const char* corP);

/**
 * @brief Define a cor da borda do retângulo.
 *
 * @param r o retângulo com a cor da borda definido.
 * @param corB Nova string da cor da borda definido.
 */
void setCorBRetangulo(RETANGULO r, const char* corB);

/**
 * @brief Libera a memória alocada para o retângulo e suas strings internas.
 * 
 * @param r O TAD Retângulo a ser destruído.
 */
void destroiRetangulo(RETANGULO r);

#endif
