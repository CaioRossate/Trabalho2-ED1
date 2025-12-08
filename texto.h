#ifndef TEXTO_H
#define TEXTO_H

/**
 * @file texto.h
 * @brief Definições do TAD Texto (formato em SVG).
 * 
 * @details
 * O arquivo texto.h declara a interface de um TAD que representa um texto
 * em um plano bidimensional. Cada texto possui um identificador, coordenadas (x,y),
 * uma âncora (i (inicio), m (meio) ou f (fim)), cores de borda e preenchimento e o conteúdo textual.
 * 
 * @param id identificador.
 * @param x coordenada x do texto.
 * @param y coordenada y do texto.
 * @param ancora âncora do texto (i, m ou f).
 * @param corB cor da borda do texto.
 * @param corP cor de preenchimento do texto.
 * @param txto conteúdo textual.
 * 
 * @return retorna um ponteiro para "TEXTO".
 */

typedef void* TEXTO;

/**
 * @brief Cria um texto com atributos específicos.
 * 
 * @param id identificador.
 * @param x coordenada x do texto.
 * @param y coordenada y do texto.
 * @param ancora âncora do texto (i, m ou f).
 * @param corB cor da borda do texto.
 * @param corP cor de preenchimento do texto.
 * @param txto string com o conteúdo do texto.
 * @param ffamily família para a fonte.
 * @param fweight peso da fonte.
 * @param fsize tamanho da fonte.
 * @return Ponteiro para TEXTO criado.
 */
TEXTO cria_texto(int id, float x, float y, char ancora, const char* corB, const char* corP, const char* txto, const char* ffamily, const char* fweight, const char* fsize);

/**
 * @brief Retorna o identificador do texto.
 * @param t ponteiro texto.
 * @return O ID da forma.
 */
int getIDTexto(TEXTO t);

/**
 * @brief Retorna a coordenada X do texto.
 * @param t ponteiro texto.
 * @return A coordenada X.
 */
float getXTexto(TEXTO t);

/**
 * @brief Retorna a coordenada Y do texto.
 * @param t ponteiro texto.
 * @return A coordenada Y.
 */
float getYTexto(TEXTO t);

/**
 * @brief Retorna o caractere de âncora (i, m ou f).
 * @param t ponteiro texto.
 * @return O caractere da âncora.
 */
char getAncoraTexto(TEXTO t);

/**
 * @brief Retorna a cor de borda do texto.
 * @param t ponteiro texto.
 * @return String da cor da borda.
 */
char* getCorBTexto(TEXTO t);

/**
 * @brief Retorna a cor de preenchimento do texto.
 * @param t ponteiro texto.
 * @return String da cor de preenchimento.
 */
char* getCorPTexto(TEXTO t);

/**
 * @brief Retorna o conteúdo textual.
 * @param t ponteiro texto.
 * @return String do conteúdo textual.
 */
char* getTxtoTexto(TEXTO t);

/**
 * @brief Obtem a fonte familia do texto.
 * @param t ponteiro do texto.
 * @return FontFamily do texto.
 */
char* getFontFamilyTexto(TEXTO t);

/**
 * @brief Obtem o peso da fonte.
 * @param t ponteiro texto.
 * @return FontWeight do texto
 */

char* getFontWeightTexto(TEXTO t);

/**
 * @brief Obtem o tamanho da fonte.
 * @param t ponteiro texto.
 * @return FontSize do texto.
 */

char* getFontSizeTexto(TEXTO t);

/**
 * @brief Calcula a área do texto (20.0 * número de caracteres).
 * @param t ponteiro texto.
 * @return A área correspondente ao texto.
 */

float getAreaTexto(TEXTO t);

/**
 * @brief Define o ID do texto.
 * @param t ponteiro texto.
 * @param id Novo ID.
 */
void setIDTexto(TEXTO t, int id);

/**
 * @brief Define a coordenada X do texto.
 * @param t ponteiro texto.
 * @param x Novo valor X.
 */
void setXTexto(TEXTO t, float x);

/**
 * @brief Define a coordenada Y do texto.
 * @param t ponteiro texto.
 * @param y Novo valor Y.
 */
void setYTexto(TEXTO t, float y);

/**
 * @brief Define a âncora do texto.
 * @param t ponteiro texto.
 * @param ancora Novo caractere de âncora (i, m ou f).
 */
void setAncoraTexto(TEXTO t, char a);

/**
 * @brief Define a cor de borda do texto.
 * @param t ponteiro texto.
 * @param corB Nova cor de borda.
 */
void setCorBTexto(TEXTO t, const char* corB);

/**
 * @brief Define a cor de preenchimento do texto.
 * @param t ponteiro texto.
 * @param corP Nova cor de preenchimento.
 */
void setCorPTexto(TEXTO t, const char* corP);

/**
 * @brief Define o conteúdo textual.
 * @param t ponteiro texto.
 * @param conteudo Nova string de conteúdo.
 */
void setTxtoTexto(TEXTO t, const char* conteudo);
 
 /**
  * @brief Define a família da fonte do texto.
  * @param t ponteiro texto.
  * @param ffamily Nova familia da fonte.
  */
 void setFontFamilyTexto(TEXTO t, const char* ffamily);
 
 /**
  * @brief Define o peso da fonte.
  * @param t ponteiro texto.
  * @param fweight Novo peso da fonte.
  */
 void setFontWeightTexto(TEXTO t, const char* fweight);
 
 /**
  * @brief Define o tamanho da fonte.
  * @param t ponteiro texto.
  * @param fsize Novo tamanho da fonte.
  */
 void setFontSizeTexto(TEXTO t, const char* fsize);

 /**
 * @brief Libera a memória alocada para o texto e suas strings internas.
 * @param t O TAD Texto a ser destruído.
 */
void destroiTexto(TEXTO t);

/**
 * @brief Calcula as coordenadas do segmento induzido pelo texto
 * @param t O texto
 * @param x1 Ponteiro para armazenar x1 do segmento
 * @param y1 Ponteiro para armazenar y1 do segmento
 * @param x2 Ponteiro para armazenar x2 do segmento
 * @param y2 Ponteiro para armazenar y2 do segmento
 */
void obtemSegmentoTexto(TEXTO t, double *x1, double *y1, double *x2, double *y2);

#endif
