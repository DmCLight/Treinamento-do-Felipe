#include "game.h"

int main(void){

/*-----------Inicialização dos componentes do Allegro-----------*/
	componentesBasicos();
/*-----------Verifica se o arquivo Highscore existe----------------*/
	verificaHighscore();
	reset_dificuldade();
/*---------Declaração das váriaveis da biblioteca Allegro---------*/
	ALLEGRO_DISPLAY *mainScreen =  NULL;
	ALLEGRO_BITMAP *bgMain = NULL;
	ALLEGRO_BITMAP *mainSelector = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_SAMPLE *mainSelect = NULL;
	ALLEGRO_SAMPLE_INSTANCE *instanceMainSelect = NULL;
/*----------------------------------------------------------------------*/

/*-----------Declaração das váriaveis do jogo em geral------------*/
	int mainSelector_w, mainSelector_h;
	float mainOption_flag = 1.0;
	bool _exit = false;
	bool _gameScreen = false, _optionScreen = false, _highscoreScreen = false, _mainScreen = true;
/*-----------------------------------------------------------------------*/

/*-----------Valores recebidos das váriaveis do Allegro------------*/
	event_queue = al_create_event_queue();
	mainScreen = al_create_display(800, 600);
	al_set_window_title(mainScreen, "The Simpsons: Snake Game");
	bgMain = al_load_bitmap("images/bgMain.png");
	mainSelector = al_load_bitmap("images/mainSelector.png");
	mainSelect = al_load_sample("sounds/mainBackground.ogg");
	instanceMainSelect = al_create_sample_instance(mainSelect);
	al_set_sample_instance_playmode(instanceMainSelect, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(instanceMainSelect, al_get_default_mixer());
/*-----------------------------------------------------------------------*/

/*--------Valores recebidos das váriaveis do jogo em geral---------*/
	mainSelector_w  = al_get_bitmap_width(mainSelector);
	mainSelector_h = al_get_bitmap_height(mainSelector);
/*-----------------------------------------------------------------------*/

/*--------Registradores/componentes de evento do Allegro--------*/
	//Teclado
	al_register_event_source(event_queue, al_get_keyboard_event_source());

/*------------------------------------------------------------------------*/

/*-----------Criação dos objetos na tela------------------------------*/
	al_draw_bitmap(bgMain, 0, 0, 0);
	al_draw_scaled_bitmap(mainSelector, 0, 0, mainSelector_w, mainSelector_h, 220, 200, 40, 40, 0);
	al_flip_display();
/*------------------------------------------------------------------------*/

/*-----------Laço Principal do jogo------------------------------*/
	//Verificação de events do jogo
	while(!_exit){

		al_play_sample_instance(instanceMainSelect);
		al_flip_display();

		if(_gameScreen == true){
			gameScreen();
			_gameScreen = false;
			_mainScreen = true;
			mainOption_flag = 1;
			al_draw_bitmap(bgMain, 0, 0, 0);
			al_draw_scaled_bitmap(mainSelector, 0, 0, mainSelector_w, mainSelector_h, 220, 200, 40, 40, 0);
			al_flip_display();
			event_queue = al_create_event_queue();
			al_register_event_source(event_queue, al_get_keyboard_event_source());
		}  else if(_optionScreen == true){	
			optionScreen();
			_optionScreen = false;
			_mainScreen = true;
			mainOption_flag = 3;
			al_draw_bitmap(bgMain, 0, 0, 0);
			al_draw_scaled_bitmap(mainSelector, 0, 0, mainSelector_w, mainSelector_h, 245, 305, 40, 40, 0);
			al_flip_display();
			event_queue = al_create_event_queue();
			al_register_event_source(event_queue, al_get_keyboard_event_source());
		}  else if(_highscoreScreen == true){
			highScoreScreen();
			_highscoreScreen = false;
			_mainScreen = true;
			mainOption_flag = 2;
			al_draw_bitmap(bgMain, 0, 0, 0);
			al_draw_scaled_bitmap(mainSelector, 0, 0, mainSelector_w, mainSelector_h, 207, 250, 40, 40, 0);
			al_flip_display();
			event_queue = al_create_event_queue();
			al_register_event_source(event_queue, al_get_keyboard_event_source());
		}  else if(_exit == true){
			break;
		} 

		while(!al_is_event_queue_empty(event_queue)){
			ALLEGRO_EVENT event;

			//Evento de escolha de opção
			al_wait_for_event(event_queue, &event);
			
			if(_mainScreen == true){
				if(event.type == ALLEGRO_EVENT_KEY_DOWN){
					if(event.keyboard.keycode == ALLEGRO_KEY_W|| event.keyboard.keycode == ALLEGRO_KEY_UP){
						if(mainOption_flag != 1 && mainOption_flag != 0){
							al_draw_bitmap(bgMain, 0, 0, 0);		
							mainOption_flag = mainOption_flag - 1;
						}
					}
				} else if(event.keyboard.keycode == ALLEGRO_KEY_S || event.keyboard.keycode == ALLEGRO_KEY_DOWN){
					if(mainOption_flag != 4){
						al_draw_bitmap(bgMain, 0, 0, 0);
						mainOption_flag = mainOption_flag + 0.5;
					}
				}

				if(mainOption_flag == 1){
					al_draw_scaled_bitmap(mainSelector, 0, 0, mainSelector_w, mainSelector_h, 220, 200, 40, 40, 0);
					al_flip_display();
				} else if(mainOption_flag == 2){
					al_draw_scaled_bitmap(mainSelector, 0, 0, mainSelector_w, mainSelector_h, 207, 250, 40, 40, 0);
					al_flip_display();
				} else if(mainOption_flag == 3){
					al_draw_scaled_bitmap(mainSelector, 0, 0, mainSelector_w, mainSelector_h, 245, 305, 40, 40, 0);
					al_flip_display();
				} else if(mainOption_flag == 4){
					al_draw_scaled_bitmap(mainSelector, 0, 0, mainSelector_w, mainSelector_h, 293, 355, 40, 40, 0);
					al_flip_display();
				}
			}
			if(event.type == ALLEGRO_EVENT_KEY_DOWN){
				if(event.keyboard.keycode == ALLEGRO_KEY_ENTER || event.keyboard.keycode == ALLEGRO_KEY_PAD_ENTER){
					switch((int)mainOption_flag){
						case 1:
							_gameScreen = true;
							_optionScreen = false;
							_highscoreScreen = false;
							break;
						case 2:
							_gameScreen = false;
							_optionScreen = false;
							_highscoreScreen = true;
							break;
						case 3:
							_gameScreen = false;
							_optionScreen = true;
							_highscoreScreen = false;
							break;
						case 4:
							_gameScreen = false;
							_optionScreen = false;
							_highscoreScreen = false;
							_exit = true;
					}
				}
			}
		}
		//Fim do evento de escolha
		al_rest(0.1);
	}
}
/*------------------------------------------------------------------*/

	// New game => al_draw_scaled_bitmap(mainSelector, 0, 0, mainSelector_w, mainSelector_h, 220, 200, 40, 40, 0);
	// Highscore => al_draw_scaled_bitmap(mainSelector, 0, 0, mainSelector_w, mainSelector_h, 200, 250, 40, 40, 0);
	// Options => al_draw_scaled_bitmap(mainSelector, 0, 0, mainSelector_w, mainSelector_h, 240, 305, 40, 40, 0);
	// Exit => al_draw_scaled_bitmap(mainSelector, 0, 0, mainSelector_w, mainSelector_h, 285, 355, 40, 40, 0);


	//gcc -o main main.c -lallegro -lallegro_primitives -lallegro_image -lallegro_ttf -lallegro_font -lallegro_audio -lallegro_acodec