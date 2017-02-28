#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

typedef struct{
	float dificuldade;
} dificuldade_jogo;
dificuldade_jogo newStructGame[1];

#define MAX 1200
int posicao_x[MAX], posicao_y[MAX], aux_x, aux2_x, aux_y, aux2_y;

char nome[15];

struct name{
	char nome[15];
	int pontuacao;
};

struct name record[3];

bool componentesBasicos(){
	if(!al_init()){
		fprintf(stderr, "Erro ao inicializar os componentes básicos do Allegro!\n");
		return false;
	}

	if(!al_init_image_addon()){
		fprintf(stderr, "Erro ao inicializar o addon de imagens do Allegro!\n");
		return false;
	}

	if(!al_install_audio()){
		fprintf(stderr, "Erro ao instalar os drivers de aúdio!\n");
		return false;
	}

	if(!al_init_acodec_addon()){
		fprintf(stderr, "Erro ao inicializar os plug-ins de aúdio\n");
		return false;
	}
	
	if(!al_install_mouse()){
		fprintf(stderr, "Erro ao instalar o mouse!\n");
		return false;
	}
	
	if(!al_install_keyboard()){
		fprintf(stderr, "Erro ao instalar o teclado!\n");
		return false;
	}
	if(!al_init_ttf_addon()){
		fprintf(stderr, "Erro ao inicializar o addon do ttf!\n");
		return false;
	}
	al_reserve_samples(1);

	return true;
}

void reset_dificuldade(){
	newStructGame[1].dificuldade = 0.04;
}

void  optionScreen(){
	ALLEGRO_FONT *fonte = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_BITMAP *mainSelector = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;

	bool facil = false, medio = false, dificil = false, _exit = false;
	int mainSelector_w, mainSelector_h;
	float mainOption_flag  = 1;
	mainSelector = al_load_bitmap("images/mainSelector.png");
	event_queue = al_create_event_queue();
	mainSelector_w  = al_get_bitmap_width(mainSelector);
	mainSelector_h = al_get_bitmap_height(mainSelector);
	fonte = al_load_font("fonts/C64.ttf", 30, 0);
	font = al_load_font("fonts/C64.ttf", 20, 0);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_textf(fonte, al_map_rgb(255, 255, 255), 400,20,ALLEGRO_ALIGN_CENTRE, "Escolha o nivel de dificuldade:");
	al_draw_textf(fonte, al_map_rgb(255, 255, 255), 370, 70,ALLEGRO_ALIGN_LEFT, "Facil");
	al_draw_scaled_bitmap(mainSelector, 0, 0, mainSelector_w, mainSelector_h, 320, 65, 40, 40, 0);
	al_draw_textf(font, al_map_rgb(255, 255, 0), 400,520,ALLEGRO_ALIGN_CENTRE, "Obs.: O jogo nao vai ficar mais facil! Se voce");
	al_draw_textf(font, al_map_rgb(255, 255, 0), 400,560,ALLEGRO_ALIGN_CENTRE, "perder o modo impossivel sera habilitado!!");
	al_flip_display();

	while(!_exit){
		while(!al_is_event_queue_empty(event_queue)){
			ALLEGRO_EVENT event;
			al_wait_for_event(event_queue, &event);

			if(!0 == true){
				if(event.type == ALLEGRO_EVENT_KEY_DOWN){
					if(event.keyboard.keycode == ALLEGRO_KEY_W|| event.keyboard.keycode == ALLEGRO_KEY_UP){
						if(mainOption_flag != 1 && mainOption_flag != 0){
							mainOption_flag = mainOption_flag - 1;
						}
					}
				} else if(event.keyboard.keycode == ALLEGRO_KEY_S || event.keyboard.keycode == ALLEGRO_KEY_DOWN){
					if(mainOption_flag < 3){
						mainOption_flag = mainOption_flag +0.5;
					}
				}

				if(mainOption_flag == 1){
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_draw_textf(fonte, al_map_rgb(255, 255, 255), 400,20,ALLEGRO_ALIGN_CENTRE, "Escolha o nivel de dificuldade:");
					al_draw_textf(fonte, al_map_rgb(255, 255, 255), 370, 70,ALLEGRO_ALIGN_LEFT, "Facil");
					al_draw_textf(font, al_map_rgb(255, 255, 0), 400,520,ALLEGRO_ALIGN_CENTRE, "Obs.: O jogo nao vai ficar mais facil! Se voce");
					al_draw_textf(font, al_map_rgb(255, 255, 0), 400,560,ALLEGRO_ALIGN_CENTRE, "perder o modo impossivel sera habilitado!!");

					al_draw_scaled_bitmap(mainSelector, 0, 0, mainSelector_w, mainSelector_h, 320, 65, 40, 40, 0);
					al_flip_display();
				} else if(mainOption_flag == 2){
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_draw_textf(fonte, al_map_rgb(255, 255, 255), 400,20,ALLEGRO_ALIGN_CENTRE, "Escolha o nivel de dificuldade:");
					al_draw_textf(fonte, al_map_rgb(255, 255, 255), 370, 70,ALLEGRO_ALIGN_LEFT, "Medio");
					al_draw_textf(font, al_map_rgb(255, 255, 0), 400,520,ALLEGRO_ALIGN_CENTRE, "Obs.: O jogo nao vai ficar mais facil! Se voce");
					al_draw_textf(font, al_map_rgb(255, 255, 0), 400,560,ALLEGRO_ALIGN_CENTRE, "perder o modo impossivel sera habilitado!!");

					al_draw_scaled_bitmap(mainSelector, 0, 0, mainSelector_w, mainSelector_h, 320, 65, 40, 40, 0);
					al_flip_display();
				} else if(mainOption_flag == 3){
					al_clear_to_color(al_map_rgb(0, 0, 0));
					al_draw_textf(fonte, al_map_rgb(255, 255, 255), 400,20,ALLEGRO_ALIGN_CENTRE, "Escolha o nivel de dificuldade:");

					al_draw_textf(fonte, al_map_rgb(255, 255, 255), 370, 70,ALLEGRO_ALIGN_LEFT, "Dificil");
					al_draw_textf(font, al_map_rgb(255, 255, 0), 400,520,ALLEGRO_ALIGN_CENTRE, "Obs.: O jogo nao vai ficar mais facil! Se voce");
					al_draw_textf(font, al_map_rgb(255, 255, 0), 400,560,ALLEGRO_ALIGN_CENTRE, "perder o modo impossivel sera habilitado!!");

					al_draw_scaled_bitmap(mainSelector, 0, 0, mainSelector_w, mainSelector_h, 320, 65, 40, 40, 0);
					al_flip_display();
				}
			}
			if(event.type == ALLEGRO_EVENT_KEY_DOWN){
				if(event.keyboard.keycode == ALLEGRO_KEY_ENTER || event.keyboard.keycode == ALLEGRO_KEY_PAD_ENTER){
					if(mainOption_flag == 1.0){
						facil = true;
						medio = false;
						dificil = false;
						_exit = true;
						break;
					}else if(mainOption_flag == 2.0){
						facil = false;
						medio = true;
						dificil = false;
						_exit = true;
						break;
					}else if(mainOption_flag == 3.0){
						facil = false;
						medio = false;
						dificil = true;
						_exit = true;
						break;
					}

				}
			}
		}// FIM DO WHILE EVENT
	}//FIM WHILE EXIT

	if(facil == true){
		newStructGame[1].dificuldade =  0.1;
	} else if(medio == true){
		newStructGame[1].dificuldade =  0.04;
	} else if(dificil == true){
		newStructGame[1].dificuldade =  0.02;
	} else{
		newStructGame[1].dificuldade =  0.1;
	}
}
		
	

void alterarHighScore(int scor){
	//--------------------------------Verifica se a potuação é maior que uma das pontuações salvas-------------------------------------------
	FILE * highscore;
	highscore = fopen("HIGHSCORE.txt", "r");
	int i;
	for(i=0; i<3; i++){//Lê todos os valores de pontução e seus respectivos nomes
		fscanf(highscore,"%s %d", record[i].nome, &record[i].pontuacao);
	}
	fclose(highscore);
	for(i=0; i<3; i++){
		if(scor > record[i].pontuacao){
			if(i == 0){//Se a pontuação for maior que a primeira pontução salva, é alterado no arquivo de texto, mudando o primeiro valor para 
				//a pontuação e alterando uma posição para baixo as demais
				highscore = fopen("HIGHSCORE.txt", "w");
				fprintf(highscore, "%s %d",nome, scor);
				fprintf(highscore, "%s %d",record[0].nome, record[0].pontuacao);
				fprintf(highscore, "%s %d",record[1].nome, record[1].pontuacao);
				fclose(highscore);
				break;
			}else if(i == 1){//Se a pontuação for maior que a segunda pontução salva, é alterado no arquivo de texto, mudando o segundo valor 
					//para a pontuação, mantendo o primero na mesma posição e alterando uma posição para baixo as demais
				highscore = fopen("HIGHSCORE.txt", "w");
				fprintf(highscore, "%s %d",record[0].nome, record[0].pontuacao);
				fprintf(highscore, "%s %d",nome, scor);
				fprintf(highscore, "%s %d",record[1].nome, record[1].pontuacao);
				fclose(highscore);
				break;
			}else if(i == 2){//Se a pontuação for maior que a terceira pontução salva, é alterado no arquivo de texto, mudando o terceiro valor e 
					//mantendo as demais na mesma posição
				highscore = fopen("HIGHSCORE.txt", "w");
				fprintf(highscore, "%s %d",record[0].nome, record[0].pontuacao);
				fprintf(highscore, "%s %d",record[1].nome, record[1].pontuacao);
				fprintf(highscore, "%s %d",nome, scor);
				fclose(highscore);
				break;
			}
		}
	}
}

//--------------------------------Limpeza dos vetores --------------------------------------------------------------------------------------
void limpaPosicoes(){
	int i;
	for(i=0; i<MAX; i++){
		posicao_x[i] = 0;
	}
	for(i=0; i<MAX; i++){
		posicao_y[i] = 0;
	}
}

bool criaSnake(float _posicao_x, float _posicao_y, int tamanho){
	//----------------------------------Declaração de variaveis e carregamento da imagem--------------------------------------------------
	ALLEGRO_BITMAP *snakeHomer;
	bool _ext;
	int i;
	snakeHomer = al_load_bitmap("images/mainSelector.png");
	//----------------------------Deslocamento dos valores (da posição x)um vetor para a direita------------------------------------------
	aux_x = posicao_x[0];
	posicao_x[0] = _posicao_x;
	for(i=1; i<MAX; i++){
		aux2_x = posicao_x[i];
		posicao_x[i] = aux_x;
		aux_x = aux2_x; 
	} 
	//----------------------------Deslocamento dos valores (da posição y)um vetor para a direita------------------------------------------
	aux_y = posicao_y[0];
	posicao_y[0] = _posicao_y;
	for(i=1; i<MAX; i++){
		aux2_y = posicao_y[i];
		posicao_y[i] = aux_y;
		aux_y = aux2_y; 
	}
	//--------------------------------------Print da cobra ate o seu tamanho atual---------------------------------------------------------------
	for(i=1; i<=tamanho; i++){
		al_draw_scaled_bitmap(snakeHomer, 0, 0, 160, 160, posicao_x[i], posicao_y[i], 20, 20, 0);
	}
	//----------------------------------Verificação de colisão na propria cobra e nas paredes laterais e inferior----------------------------
	for(i=1; i<=tamanho; i++){
		if(posicao_x[0] == posicao_x[i] && posicao_y[0] == posicao_y[i]){
			_ext = true;
			break;
		}else{
			_ext = false;
		}
	}
	return _ext;
}

void game(){
	const float gambiarra = newStructGame[1].dificuldade;
	//----------------------------------------Declaração de Variaveis--------------------------------------------------------------
	bool _exit = false, _objectCreate = false;
	int _position_flag = 2, score = 0;
	float _object_position_x1, _object_position_y1, _position_x1, _position_y1;
	_position_x1 = 0.0;
	_position_y1 = 20.0;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_BITMAP *snakeHomer[4];
	ALLEGRO_BITMAP *object;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_FONT *fonte = NULL;

	limpaPosicoes();
	//-----------------------------------------Carregamento de fonte e imagens----------------------------------------------------
	font = al_load_font("fonts/C64.ttf", 20, 0);
	fonte = al_load_font("fonts/C64.ttf", 55, 0);

	snakeHomer[0] = al_load_bitmap("images/cabeca1.png");
	snakeHomer[1] = al_load_bitmap("images/cabeca2.png");
	snakeHomer[2] = al_load_bitmap("images/cabeca3.png");
	snakeHomer[3] = al_load_bitmap("images/cabeca4.png");

	object = al_load_bitmap("images/mainSelector.png");
	//-----------------------------------------Criação de Filas de Eventos-------------------------------------------------------------
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	//---------------------------------------------------------------------------------------------------------------------------------------

	al_draw_scaled_bitmap(snakeHomer[0], 0, 0, 160, 160, _position_x1, _position_y1, 20, 20, 0);

	srand( (unsigned)time(NULL) );

	while(!_exit){
	
	//-------------------------------------------------------Teste de colisão da cobra com os Objetos--------------------------------
		if((_position_x1 == _object_position_x1) && (_position_y1 == _object_position_y1)){
			_objectCreate = false;
			score++;	
		}
	//------------------------------------------------Criação dos objetos para serem capturados--------------------------------------
		while(_objectCreate == false){
			_object_position_x1 = rand() % 800;
			_object_position_y1 = rand() % 600;
			
			while((int)_object_position_x1 % 20 != 0){//Se o objeto não for multiplo de 20 ele soma 1 até que o valor da posição seja multiplo de 20
				_object_position_x1++;
			}

			while((int)_object_position_y1 % 20 != 0){//Se o objeto não for multiplo de 20 ele soma 1 até que o valor da posição seja multiplo de 20
				_object_position_y1++;
			}

			if(_object_position_x1 < 0.0){//Se o valor de x do objeto for menor que 0(fora da tela) ele muda o valor para 0
				_object_position_x1 = 0.0;
			} else if(_object_position_x1 > 780.0){//Se o valor de x do objeto for menor que 780(fora da tela) ele muda o valor para diminui o valor em 20
				_object_position_x1 -= 20.0;
			}

			if(_object_position_y1 < 20.0){//Se o valor de x do objeto for menor que 20(acima da barra branca) ele muda o valor para 20
				_object_position_y1 = 20.0;
			} else if(_object_position_y1 > 580.0){//Se o valor de x do objeto for menor que 580(fora da tela) ele muda o valor para diminui o valor em 20
				_object_position_y1 -= 20.0;
			}
			_objectCreate = true;
		}

		if(_objectCreate == true){
			al_draw_scaled_bitmap(object, 0, 0, 160, 160, _object_position_x1, _object_position_y1, 20, 20, 0);
		}
	//----------------------------------------------Fim da criação do objeto e atualização da tela a seguir-----------------------------------
		al_flip_display();
	//------------------------------------------------------Movimentação da Cobra--------------------------------------------------------------
		if(_position_flag == 1 && _position_y1 > 20){
			_position_y1 -= 20;
		} else if(_position_flag == 2 && _position_x1 < 780){
			_position_x1 += 20.0;
		} else if(_position_flag == 3 && _position_y1 < 580){
			_position_y1 += 20;
		} else if(_position_flag == 4 && _position_x1 > 0){
			_position_x1 -= 20.0;
		}
		al_clear_to_color(al_map_rgb(0, 0, 0));
	//--------------------------------------------------Chama a função criaSnake-----------------------------------------------------------
		_exit = criaSnake(_position_x1, _position_y1, score+2);
	//---------------------------------------------Print do Nome do jogador e Pontuação--------------------------------------------------
		al_draw_filled_rectangle(0.0, 0.0, 800.0, 20.0, al_map_rgb(255, 255, 255));
		al_draw_textf(font, al_map_rgb(255, 0, 0), 40, 1, ALLEGRO_ALIGN_LEFT, "Player: %s", nome);
		al_draw_textf(font, al_map_rgb(255, 0, 0), 500, 1, ALLEGRO_ALIGN_LEFT, "Score: %d", score*10);
		al_rest(gambiarra);
	//--------------------------------------------------Teste de colisão com a parte superior da tela-------------------------------------
		if(_position_y1 < 20){
			_exit = true;
			break;
		}
	//--------------------------------------------------Alteração da cabeça em relação a direção-----------------------------------------
		if(_position_flag == 2){
			al_draw_scaled_bitmap(snakeHomer[0], 0, 0, 160, 160, _position_x1, _position_y1, 20, 20, 0);
		}else if(_position_flag == 3){
			al_draw_scaled_bitmap(snakeHomer[1], 0, 0, 160, 160, _position_x1, _position_y1, 20, 20, 0);
		}else if(_position_flag == 4){
			al_draw_scaled_bitmap(snakeHomer[2], 0, 0, 160, 160, _position_x1, _position_y1, 20, 20, 0);
		}else if(_position_flag == 1){
			al_draw_scaled_bitmap(snakeHomer[3], 0, 0, 160, 160, _position_x1, _position_y1, 20, 20, 0);
		}
	//-----------------------------------------Alteração da direção quando uma das teclas é pressionada-------------------------------

		while(!al_is_event_queue_empty(event_queue)){
			ALLEGRO_EVENT event;
			al_wait_for_event(event_queue, &event);

			if(event.type == ALLEGRO_EVENT_KEY_DOWN){
				if((event.keyboard.keycode == ALLEGRO_KEY_W || event.keyboard.keycode == ALLEGRO_KEY_UP) && _position_flag != 3){
					_position_flag = 1;
					break;
				} else if((event.keyboard.keycode == ALLEGRO_KEY_D || event.keyboard.keycode == ALLEGRO_KEY_RIGHT) && _position_flag != 4){
					_position_flag = 2;
					break;
				} else if((event.keyboard.keycode == ALLEGRO_KEY_S || event.keyboard.keycode == ALLEGRO_KEY_DOWN) && _position_flag != 1){
					_position_flag = 3;
					break;
				} else if((event.keyboard.keycode == ALLEGRO_KEY_A || event.keyboard.keycode == ALLEGRO_KEY_LEFT) && _position_flag != 2){
					_position_flag = 4;
					break;
				}

			}//FIM DO IF EVENT TYPE

		}//FIM WHILE DO EVENTO
		
	}//FIM DO LAÇO PRINCIPAL
	if(score >= 1160){//Verifica se o jogador alcançou a pontução necessária para vencer
		al_clear_to_color(al_map_rgb(0,0,0));
		al_draw_text(fonte, al_map_rgb(0, 255, 0), 400, 300, ALLEGRO_ALIGN_CENTRE, "You Win!");
		al_flip_display();
		al_rest(1.5);

	}else{
		al_clear_to_color(al_map_rgb(0,0,0));
		al_draw_text(fonte, al_map_rgb(255, 0, 0), 400, 300, ALLEGRO_ALIGN_CENTRE, "Game Over!");
		al_flip_display();
		al_rest(1.5);
	}
	alterarHighScore(score*10);
}

void name(){
	//-----------------------------------------Carregamento de fonte e imagens----------------------------------------------------
	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_FONT *fonte = NULL;
	fonte = al_load_font("fonts/C64.ttf", 40, 0);
	font = al_load_font("fonts/C64.ttf", 30, 0);
	//-----------------------------------------Criação de Filas de Eventos-------------------------------------------------------------
	fila_eventos = al_create_event_queue();
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());

	bool _exit = false;
	strcpy(nome,"");

	al_clear_to_color(al_map_rgb(0,0,0));
	al_draw_textf(fonte, al_map_rgb(255, 255, 255), 400, 280, ALLEGRO_ALIGN_CENTRE, "Digite seu nome");
	al_flip_display();
	
	while(!_exit){
		while (!al_is_event_queue_empty(fila_eventos)){
			ALLEGRO_EVENT evento;
			al_wait_for_event(fila_eventos, &evento);
			if (evento.type == ALLEGRO_EVENT_KEY_CHAR){
				char atual[] = {evento.keyboard.unichar, '\0'};
				if (strlen(nome) <= 14){
					if (evento.keyboard.unichar >= 'A' &&  evento.keyboard.unichar <= 'Z'){
						strcat(nome, atual);//Adiciona a string "atual" na string "nome"
					}else if (evento.keyboard.unichar >= 'a' &&  evento.keyboard.unichar <= 'z'){
						strcat(nome, atual);//Adiciona a string "atual" na string "nome"
					}
				}
				al_clear_to_color(al_map_rgb(0,0,0));
				al_draw_textf(fonte, al_map_rgb(255, 255, 255), 400, 280, ALLEGRO_ALIGN_CENTRE, "Digite seu nome");
				al_draw_textf(font, al_map_rgb(255, 255, 255), 400, 350, ALLEGRO_ALIGN_CENTRE, "%s", nome);
				al_flip_display();
			}
			if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(nome) != 0){
				nome[strlen(nome) - 1] = '\0';
			}
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ENTER && strlen(nome)>0){
				_exit = true;
			}
		}
	}
}

void gameScreen(){
	bool _exit = false;
	float i;
	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_FONT *fonte = NULL;
	
	fonte = al_load_font("fonts/C64.ttf", 55, 0);
	font = al_load_font("fonts/C64.ttf", 15, 0);
	name();

	while(!_exit){
		game();
		_exit = true;
		al_clear_to_color(al_map_rgb(0,0,0));
		fila_eventos = al_create_event_queue();
		al_register_event_source(fila_eventos, al_get_keyboard_event_source());
		for(i = 5; i > 0; i -= 0.1){
			al_clear_to_color(al_map_rgb(0,0,0));
			al_draw_textf(fonte, al_map_rgb(255, 255, 255), 400, 280, ALLEGRO_ALIGN_CENTRE, "Continue?	%.0f", i);
			al_draw_textf(font, al_map_rgb(255, 0, 0), 400, 350, ALLEGRO_ALIGN_CENTRE, "Pressione ENTER para jogar novamente");
			al_flip_display();
			while(!al_is_event_queue_empty(fila_eventos)){
				ALLEGRO_EVENT evento;
				al_wait_for_event(fila_eventos, &evento);
				if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
					if(evento.keyboard.keycode == ALLEGRO_KEY_ENTER){
						i = 0;
						_exit = false;
						break;
					}
				}
			}
			al_rest(0.1);
		}
	}
} 

//--------------------------------------------------------Leitura da pontuação que está salva no arquivo--------------------------- 
void HIGHSCORE(){
	FILE * highscore;
	int i;
	highscore = fopen("HIGHSCORE.txt", "r");
	for(i=0; i<3; i++){
		fscanf(highscore,"%s %d", record[i].nome, &record[i].pontuacao);
	}

	al_flip_display();
	fclose(highscore);
}

//----------------------------------------------------------Mostra as 3 maiores pontuções dos jogadores--------------------------
void highScoreScreen(){
	bool sair = true;

	ALLEGRO_EVENT_QUEUE * fila_eventos = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_FONT *fonte = NULL;
	ALLEGRO_BITMAP * HIGHSCOREIMAGEM[2];
	FILE * highscore;
	fonte = al_load_font("fonts/C64.ttf", 25, 0);
	fila_eventos = al_create_event_queue();
	al_register_event_source(fila_eventos, al_get_keyboard_event_source());
	HIGHSCOREIMAGEM[0] = al_load_bitmap("images/highscore1.png");
	HIGHSCOREIMAGEM[1] = al_load_bitmap("images/highscore2.png");

	highscore = fopen("HIGHSCORE.txt", "r");
	event_queue = al_create_event_queue();
	ALLEGRO_EVENT evento;
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	ALLEGRO_BITMAP *mainSelector = al_create_bitmap(10, 10);
	

	int  mainOption_flag = 1;
	HIGHSCORE();
	mainSelector = al_load_bitmap("images//mainSelector.png");	
	al_draw_bitmap(HIGHSCOREIMAGEM[0], 0, 0, 0);
	al_draw_scaled_bitmap(mainSelector, 0, 0, 160, 160, 25, 505, 30, 30, 0);


	al_draw_textf(fonte, al_map_rgb(255, 255, 255), 20,255,ALLEGRO_ALIGN_LEFT, "%s", record[0].nome);
	al_draw_textf(fonte, al_map_rgb(255, 255, 255), 575, 255, ALLEGRO_ALIGN_LEFT, "%d", record[0].pontuacao);
	al_draw_textf(fonte, al_map_rgb(255, 255, 255), 20, 335 ,ALLEGRO_ALIGN_LEFT,"%s", record[1].nome);
	al_draw_textf(fonte, al_map_rgb(255, 255, 255), 575, 335, ALLEGRO_ALIGN_LEFT, "%d", record[1].pontuacao);
	al_draw_textf(fonte, al_map_rgb(255, 255, 255), 20,415,ALLEGRO_ALIGN_LEFT, "%s", record[2].nome);
	al_draw_textf(fonte, al_map_rgb(255, 255, 255), 575, 415, ALLEGRO_ALIGN_LEFT, "%d", record[2].pontuacao);

			
	al_flip_display();


	while(sair){
		while(!al_is_event_queue_empty(fila_eventos)){
			HIGHSCORE();
			al_wait_for_event(fila_eventos, &evento);
			if (evento.type == ALLEGRO_EVENT_KEY_DOWN){
				switch(evento.keyboard.keycode){
					case ALLEGRO_KEY_LEFT:
						mainOption_flag = 1;
						break;
					case ALLEGRO_KEY_RIGHT:
						mainOption_flag = 2;
						break;
				}
			}
			if (mainOption_flag == 1){
				al_draw_bitmap(HIGHSCOREIMAGEM[0], 0, 0, 0);
				al_draw_scaled_bitmap(mainSelector, 0, 0, 160, 160, 25, 505, 30, 30, 0);

				al_draw_textf(fonte, al_map_rgb(255, 255, 255), 20,255,ALLEGRO_ALIGN_LEFT, "%s", record[0].nome);
				al_draw_textf(fonte, al_map_rgb(255, 255, 255), 575, 255, ALLEGRO_ALIGN_LEFT, "%d", record[0].pontuacao);
				al_draw_textf(fonte, al_map_rgb(255, 255, 255), 20, 335 ,ALLEGRO_ALIGN_LEFT,"%s", record[1].nome);
				al_draw_textf(fonte, al_map_rgb(255, 255, 255), 575, 335, ALLEGRO_ALIGN_LEFT, "%d", record[1].pontuacao);
				al_draw_textf(fonte, al_map_rgb(255, 255, 255), 20,415,ALLEGRO_ALIGN_LEFT, "%s", record[2].nome);
				al_draw_textf(fonte, al_map_rgb(255, 255, 255), 575, 415, ALLEGRO_ALIGN_LEFT, "%d", record[2].pontuacao);


				if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
					if(evento.keyboard.keycode == ALLEGRO_KEY_ENTER){
						sair = false;
					}
				}		
			}else{
				al_draw_bitmap(HIGHSCOREIMAGEM[1], 0, 0, 0);
				al_draw_scaled_bitmap(mainSelector, 0, 0, 160, 160, 575, 505, 30, 30, 0);

				al_draw_textf(fonte, al_map_rgb(255, 255, 255), 20,255,ALLEGRO_ALIGN_LEFT, "%s", record[0].nome);
				al_draw_textf(fonte, al_map_rgb(255, 255, 255), 575, 255, ALLEGRO_ALIGN_LEFT, "%d", record[0].pontuacao);
				al_draw_textf(fonte, al_map_rgb(255, 255, 255), 20, 335 ,ALLEGRO_ALIGN_LEFT,"%s", record[1].nome);
				al_draw_textf(fonte, al_map_rgb(255, 255, 255), 575, 335, ALLEGRO_ALIGN_LEFT, "%d", record[1].pontuacao);
				al_draw_textf(fonte, al_map_rgb(255, 255, 255), 20,415,ALLEGRO_ALIGN_LEFT, "%s", record[2].nome);
				al_draw_textf(fonte, al_map_rgb(255, 255, 255), 575, 415, ALLEGRO_ALIGN_LEFT, "%d", record[2].pontuacao);


				if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
					if(evento.keyboard.keycode == ALLEGRO_KEY_ENTER){
						highscore = fopen("HIGHSCORE.txt", "w");
						fprintf(highscore, "- 0\n- 0\n- 0");
						fclose(highscore);
					}
				}
			}
		}
		al_flip_display();
	}	
}

//----------------------------------------------Verifica se o arquivo de armazenamento da pontuação foi criado-----------------------------------
void verificaHighscore(){
	FILE * highscore;
	highscore = fopen("HIGHSCORE.txt", "r");
	if(highscore == NULL){
		printf("O arquivo HIGHSCORE.txt nao pode ser aberto\n");
		highscore = fopen("HIGHSCORE.txt", "w");
		fprintf(highscore, "- 0\n- 0\n- 0");
		fclose(highscore);
	}
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
