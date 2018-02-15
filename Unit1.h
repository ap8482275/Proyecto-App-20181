//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Media.hpp>

#define BLANCO 0
#define NEGRO 1
//---------------------------------------------------------------------------

class Ficha{
	public:
		TCircle *elemento;
		int tam;
		int posX,posY;
		bool visible;
		int tipo;

		Ficha(){
			tam = 50;
			visible = false;
			tipo = -1;
		}

		void set_tamano(int _tam){
			tam = _tam;
			elemento->Width = tam;
			elemento->Height = tam;
		}

		void set_visible(bool _visible){
			visible = _visible;
			elemento->Visible = visible;
		}

		void set_tipo(int _tipo){
			tipo = _tipo;
			//#FFE0E0E0
			if(tipo == NEGRO)
				elemento->Fill->Color = 0xFF000000;
			if(tipo == BLANCO)
				elemento->Fill->Color = 0xFFFFFFFF;
			if(tipo == -1)
				elemento->Fill->Color = 0xFFE0E0E0;
		}

		void crear_ficha(int _posx, int _posy, int n){
			posX = _posx;
			posY = _posy;

			/*if(elemento == NULL){
				elemento = new TCircle(this);
				elemento->Parent = this;
				elemento->Name = "Ficha"+IntToStr(n);
			}*/
			if(elemento != NULL){
				elemento->Position->X = posX;
				elemento->Position->Y = posY;
				elemento->Visible = visible;
				elemento->Width = tam;
				elemento->Height = tam;

				//#FFE0E0E0
				if(tipo == NEGRO)
					elemento->Fill->Color = 0xFF000000;
				if(tipo == BLANCO)
					elemento->Fill->Color = 0xFFFFFFFF;
			}
		}
};

class Tablero{
	public:
	int tam_ficha;
	int mapa[8][8];
	int turno;
	bool iniciado;
	int posF,posC;
	Ficha fichas[64];

	int contar_blancas(){
		int contador = 0;
		
		for(int f=0; f<8; f++)
			for(int c=0; c<8; c++)
				if(mapa[f][c] == BLANCO)
					contador++;			

		return contador;
	}

	int contar_negras(){
		int contador = 0;

		for(int f=0; f<8; f++)
			for(int c=0; c<8; c++)
				if(mapa[f][c] == NEGRO)
					contador++;

		return contador;
	}
	
	void inicializar(){
		for(int f=0; f<8; f++)
			for(int c=0; c<8; c++){
				mapa[f][c] = -1;
				fichas[f*8 + c].set_tamano(tam_ficha);
				fichas[f*8 + c].set_visible(false);
				fichas[f*8 + c].set_tipo(-1);
				fichas[f*8 + c].crear_ficha(c*tam_ficha,f*tam_ficha,f*8 + c);
			}

		turno = Random(2);
		for(int f=3; f<=4; f++)
			for(int c=3; c<=4; c++){
				if(f==3 && c==4){
					turno = !turno;
				}
				if(f==4 && c==4){
					turno = !turno;
				}
				mapa[f][c] = turno;
				fichas[f*8 + c].set_tipo(turno);
				fichas[f*8 + c].set_visible(true);				
			}

		for(int f=0; f<8; f++)
			for(int c=0; c<8; c++){
				//fichas[f*8 + c].set_visible(true);
			}
	}

	void repintar(){
		for(int f=0; f<8; f++)
			for(int c=0; c<8; c++){
				fichas[f*8 + c].set_tipo(mapa[f][c]);
				if(mapa[f][c] != -1)
					fichas[f*8 + c].set_visible(true);				
			}
	}

	bool validar_jugada(int fila, int col){
		int f,c;
		
		if(mapa[fila][col] == -1){
			bool condicion = false;
			
			//Validar Verticalmente Arriba			
			f = fila;
			c = col;
			if(f > 0)
				if(mapa[f-1][c] == !turno){
					while(f > 0){
						/*if(mapa[f-1][c] == -1){
							return true;
						}*/
						if(mapa[f-1][c] == turno){
							return true;
						}
						if(mapa[f-1][c] == -1){
							break;
						}
						f--;
					}
				}

			//Validar Verticalmente Abajo			
			f = fila;
			c = col;
			if(f < 7)
				if(mapa[f+1][c] == !turno){
					while(f < 7){
						if(mapa[f+1][c] == turno){
							return true;
						}
						if(mapa[f+1][c] == -1){
							break;
						}
						f++;
					}
				}

			//Validar Horizontalmente Izquierda			
			f = fila;
			c = col;
			if(c > 0)
				if(mapa[f][c-1] == !turno){
					while(c > 0){
						if(mapa[f][c-1] == turno){
							return true;
						}
						if(mapa[f][c-1] == -1){
							break;
						}
						c--;
					}
				}

			//Validar Horizontalmente Derecha
			f = fila;
			c = col;
			if(c < 7)
				if(mapa[f][c+1] == !turno){
					while(c < 7){
						if(mapa[f][c+1] == turno){
							return true;
						}
						if(mapa[f][c+1] == -1){
							break;
						}
						c++;
					}
				}



			//Validar Diagonal Arriba Izquierda
			f = fila;
			c = col;
			if(f > 0 && c > 0)
				if(mapa[f-1][c-1] == !turno){
					while(f > 0 && c > 0){
						if(mapa[f-1][c-1] == turno){
							return true;
						}
						if(mapa[f-1][c-1] == -1){
							break;
						}
						f--;
						c--;
					}
				}

			//Validar Diagonal Abajo Izquierda
			f = fila;
			c = col;
			if(f < 7 && c > 0)
				if(mapa[f+1][c-1] == !turno){
					while(f < 7 && c > 0){
						if(mapa[f+1][c-1] == turno){
							return true;
						}
						if(mapa[f+1][c-1] == -1){
							break;
						}
						f++;
						c--;
					}
				}

			//Validar Diagonal Arriba Derecha
			f = fila;
			c = col;
			if(f > 0 && c < 7)
				if(mapa[f-1][c+1] == !turno){
					while(f > 0 && c < 7){
						if(mapa[f-1][c+1] == turno){
							return true;
						}
						if(mapa[f-1][c+1] == -1){
							break;
						}
						f--;
						c++;
					}
				}	

			//Validar Diagonalmente Abajo Derecha
			f = fila;
			c = col;
			if(f < 7 && c < 7)
				if(mapa[f+1][c+1] == !turno){
					while(f < 7 && c < 7){
						if(mapa[f+1][c+1] == turno){
							return true;
						}
						if(mapa[f+1][c+1] == -1){
							break;
						}
						f++;
						c++;
					}
				}	
			
		}

		return false;
	}

	void cambiar_fichas(int fila, int col){
		int f,c;
		bool condicion;
		
		if(mapa[fila][col] == -1){
			//Validar Verticalmente Arriba			
			f = fila;
			c = col;
			condicion = false;
			if(f > 0)
				if(mapa[f-1][c] == !turno){
					while(f > 0){
						if(mapa[f-1][c] == turno){
							condicion = true;
                            break;
						}
						if(mapa[f-1][c] == -1){
							condicion = false;
							break;
						}
						f--;
					}
				}
				if(condicion){
					f = fila;
					c = col;
					while(f > 0){
						if(mapa[f-1][c] == turno)
							break;
						mapa[f-1][c] = turno;
						f--;
					}
				}

			//Validar Verticalmente Abajo
			f = fila;
			c = col;
			condicion = false;
			if(f < 7)
				if(mapa[f+1][c] == !turno){
					while(f < 7){
						if(mapa[f+1][c] == turno){
							condicion = true;
                            break;
						}
						if(mapa[f+1][c] == -1){
							condicion = false;
							break;
						}
						f++;
					}
				}
			if(condicion){
					f = fila;
					c = col;
					while(f < 7){
						if(mapa[f+1][c] == turno)
							break;
						mapa[f+1][c] = turno;
						f++;
					}
				}

			//Validar Horizontalmente Izquierda			
			f = fila;
			c = col;
			condicion = false;
			if(c > 0)
				if(mapa[f][c-1] == !turno){
					while(c > 0){
						if(mapa[f][c-1] == turno){
							condicion = true;
                            break;
						}
						if(mapa[f][c-1] == -1){
							condicion = false;
							break;
						}
						c--;
					}
				}
			if(condicion){
					f = fila;
					c = col;
					while(c > 0){
						if(mapa[f][c-1] == turno)
							break;
						mapa[f][c-1] = turno;
						c--;
					}
				}

			//Validar Horizontalmente Derecha
			f = fila;
			c = col;
			condicion = false;
			if(c < 7)
				if(mapa[f][c+1] == !turno){
					while(c < 7){
						if(mapa[f][c+1] == turno){
							condicion = true;
                            break;
						}
						if(mapa[f][c+1] == -1){
							condicion = false;
							break;
						}
						c++;
					}
				}
				if(condicion){
					f = fila;
					c = col;
					while(c < 7){
						if(mapa[f][c+1] == turno)
							break;
						mapa[f][c+1] = turno;
						c++;
					}
				}



			//Validar Diagonal Arriba Izquierda
			f = fila;
			c = col;
			condicion = false;
			if(f > 0 && c > 0)
				if(mapa[f-1][c-1] == !turno){
					while(f > 0 && c > 0){
						if(mapa[f-1][c-1] == turno){
							condicion = true;
                            break;
						}
						if(mapa[f-1][c-1] == -1){
							condicion = false;
							break;
						}
						f--;
						c--;
					}
				}
				if(condicion){
					f = fila;
					c = col;
					while(f > 0 && c > 0){
						if(mapa[f-1][c-1] == turno)
							break;
						mapa[f-1][c-1] = turno;
						f--;
						c--;
					}
				}

			//Validar Diagonal Abajo Izquierda
			f = fila;
			c = col;
			condicion = false;
			if(f < 7 && c > 0)
				if(mapa[f+1][c-1] == !turno){
					while(f < 7 && c > 0){
						if(mapa[f+1][c-1] == turno){
							condicion = true;
                            break;
						}
						if(mapa[f+1][c-1] == -1){
							condicion = false;
							break;
						}
						f++;
						c--;
					}
				}
			if(condicion){
					f = fila;
					c = col;
					while(f < 7 && c > 0){
						if(mapa[f+1][c-1] == turno)
							break;
						mapa[f+1][c-1] = turno;
						f++;
						c--;
					}
				}

			//Validar Diagonal Arriba Derecha
			f = fila;
			c = col;
			condicion = false;
			if(f > 0 && c < 7)
				if(mapa[f-1][c+1] == !turno){
					while(f > 0 && c < 7){
						if(mapa[f-1][c+1] == turno){
							condicion = true; 
							break;
						}if(mapa[f-1][c+1] == -1){
							condicion = false;
							break;
						}
						f--;
						c++;
					}
				}	
			if(condicion){
					f = fila;
					c = col;
					while(f > 0 && c < 7){
						if(mapa[f-1][c+1] == turno)
							break;
						mapa[f-1][c+1] = turno;						
						f--;
						c++;
					}
				}

			//Validar Diagonalmente Abajo Derecha
			f = fila;
			c = col;
			condicion = false;
			if(f < 7 && c < 7)
				if(mapa[f+1][c+1] == !turno){
					while(f < 7 && c < 7){
						if(mapa[f+1][c+1] == turno){
							condicion = true; 
							break;
						}
						if(mapa[f+1][c+1] == -1){
							condicion = false;
							break;
						}
						f++;
						c++;
					}
				}	
			if(condicion){
					f = fila;
					c = col;
					while(f < 7 && c < 7){
						if(mapa[f+1][c+1] == turno)
							break;
						mapa[f+1][c+1] = turno;
						f++;
						c++;
					}
				}
			
		}
	}

	bool gameOver(){
		for(int f=0; f<7; f++)
			for(int c=0; c<7; c++)
				if(validar_jugada(f,c))
					return false;
        return true;
	}

	void jugarMaquina(){
		int f,c;
		bool condicion;

		int fMax, cMax, maxFichas = 0;
		int mapaAux[8][8];

		for(int f=0; f<8; f++)
			for(int c=0; c<8; c++)
				mapaAux[f][c] = mapa[f][c];

		for(int fila=0; fila<7; fila++)
			for(int col=0; col<7; col++)
				if(validar_jugada(fila,col)){
					if(mapaAux[fila][col] == -1){
						//Validar Verticalmente Arriba
						f = fila;
						c = col;
						condicion = false;
						if(f > 0)
							if(mapaAux[f-1][c] == !turno){
								while(f > 0){
									if(mapaAux[f-1][c] == turno){
										condicion = true;
										break;
									}
									if(mapaAux[f-1][c] == -1){
										condicion = false;
										break;
									}
									f--;
								}
							}
							if(condicion){
								f = fila;
								c = col;
								while(f > 0){
									if(mapaAux[f-1][c] == turno)
										break;
									mapaAux[f-1][c] = turno;
									f--;
								}
							}

						//Validar Verticalmente Abajo
						f = fila;
						c = col;
						condicion = false;
						if(f < 7)
							if(mapaAux[f+1][c] == !turno){
								while(f < 7){
									if(mapaAux[f+1][c] == turno){
										condicion = true;
										break;
									}
									if(mapaAux[f+1][c] == -1){
										condicion = false;
										break;
									}
									f++;
								}
							}
						if(condicion){
								f = fila;
								c = col;
								while(f < 7){
									if(mapaAux[f+1][c] == turno)
										break;
									mapaAux[f+1][c] = turno;
									f++;
								}
							}

						//Validar Horizontalmente Izquierda
						f = fila;
						c = col;
						condicion = false;
						if(c > 0)
							if(mapaAux[f][c-1] == !turno){
								while(c > 0){
									if(mapaAux[f][c-1] == turno){
										condicion = true;
										break;
									}
									if(mapaAux[f][c-1] == -1){
										condicion = false;
										break;
									}
									c--;
								}
							}
						if(condicion){
								f = fila;
								c = col;
								while(c > 0){
									if(mapaAux[f][c-1] == turno)
										break;
									mapaAux[f][c-1] = turno;
									c--;
								}
							}

						//Validar Horizontalmente Derecha
						f = fila;
						c = col;
						condicion = false;
						if(c < 7)
							if(mapaAux[f][c+1] == !turno){
								while(c < 7){
									if(mapaAux[f][c+1] == turno){
										condicion = true;
										break;
									}
									if(mapaAux[f][c+1] == -1){
										condicion = false;
										break;
									}
									c++;
								}
							}
							if(condicion){
								f = fila;
								c = col;
								while(c < 7){
									if(mapaAux[f][c+1] == turno)
										break;
									mapaAux[f][c+1] = turno;
									c++;
								}
							}



						//Validar Diagonal Arriba Izquierda
						f = fila;
						c = col;
						condicion = false;
						if(f > 0 && c > 0)
							if(mapaAux[f-1][c-1] == !turno){
								while(f > 0 && c > 0){
									if(mapaAux[f-1][c-1] == turno){
										condicion = true;
										break;
									}
									if(mapaAux[f-1][c-1] == -1){
										condicion = false;
										break;
									}
									f--;
									c--;
								}
							}
							if(condicion){
								f = fila;
								c = col;
								while(f > 0 && c > 0){
									if(mapaAux[f-1][c-1] == turno)
										break;
									mapaAux[f-1][c-1] = turno;
									f--;
									c--;
								}
							}

						//Validar Diagonal Abajo Izquierda
						f = fila;
						c = col;
						condicion = false;
						if(f < 7 && c > 0)
							if(mapaAux[f+1][c-1] == !turno){
								while(f < 7 && c > 0){
									if(mapaAux[f+1][c-1] == turno){
										condicion = true;
										break;
									}
									if(mapaAux[f+1][c-1] == -1){
										condicion = false;
										break;
									}
									f++;
									c--;
								}
							}
						if(condicion){
								f = fila;
								c = col;
								while(f < 7 && c > 0){
									if(mapaAux[f+1][c-1] == turno)
										break;
									mapaAux[f+1][c-1] = turno;
									f++;
									c--;
								}
							}

						//Validar Diagonal Arriba Derecha
						f = fila;
						c = col;
						condicion = false;
						if(f > 0 && c < 7)
							if(mapaAux[f-1][c+1] == !turno){
								while(f > 0 && c < 7){
									if(mapaAux[f-1][c+1] == turno){
										condicion = true;
										break;
									}if(mapaAux[f-1][c+1] == -1){
										condicion = false;
										break;
									}
									f--;
									c++;
								}
							}
						if(condicion){
								f = fila;
								c = col;
								while(f > 0 && c < 7){
									if(mapaAux[f-1][c+1] == turno)
										break;
									mapaAux[f-1][c+1] = turno;
									f--;
									c++;
								}
							}

						//Validar Diagonalmente Abajo Derecha
						f = fila;
						c = col;
						condicion = false;
						if(f < 7 && c < 7)
							if(mapaAux[f+1][c+1] == !turno){
								while(f < 7 && c < 7){
									if(mapaAux[f+1][c+1] == turno){
										condicion = true;
										break;
									}
									if(mapaAux[f+1][c+1] == -1){
										condicion = false;
										break;
									}
									f++;
									c++;
								}
							}
						if(condicion){
								f = fila;
								c = col;
								while(f < 7 && c < 7){
									if(mapaAux[f+1][c+1] == turno)
										break;
									mapaAux[f+1][c+1] = turno;
									f++;
									c++;
								}
							}

					}

					int contador = 0;
					for(int f=0; f<8; f++)
						for(int c=0; c<8; c++)
							if(mapaAux[f][c] == NEGRO)
								contador++;
					if(contador > maxFichas){
						fMax = fila;
						cMax = col;
                        maxFichas = contador;
					}
				}

		cambiar_fichas(fMax,cMax);
		mapa[fMax][cMax] = turno;
	}

	Tablero(){		
		//inicializar();
	}

	void set_tam(int _tam){
		tam_ficha = _tam;		
	}

	friend void sincronizar(Tablero &tablero);
};

class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *Button1;
	TCircle *Circle1;
	TCircle *Circle2;
	TCircle *Circle3;
	TCircle *Circle4;
	TCircle *Circle5;
	TCircle *Circle6;
	TCircle *Circle7;
	TCircle *Circle8;
	TCircle *Circle9;
	TCircle *Circle10;
	TCircle *Circle11;
	TCircle *Circle12;
	TCircle *Circle13;
	TCircle *Circle14;
	TCircle *Circle15;
	TCircle *Circle16;
	TCircle *Circle17;
	TCircle *Circle18;
	TCircle *Circle19;
	TCircle *Circle20;
	TCircle *Circle21;
	TCircle *Circle22;
	TCircle *Circle23;
	TCircle *Circle24;
	TCircle *Circle25;
	TCircle *Circle26;
	TCircle *Circle27;
	TCircle *Circle28;
	TCircle *Circle29;
	TCircle *Circle30;
	TCircle *Circle31;
	TCircle *Circle32;
	TCircle *Circle33;
	TCircle *Circle34;
	TCircle *Circle35;
	TCircle *Circle36;
	TCircle *Circle37;
	TCircle *Circle38;
	TCircle *Circle39;
	TCircle *Circle40;
	TCircle *Circle41;
	TCircle *Circle42;
	TCircle *Circle43;
	TCircle *Circle44;
	TCircle *Circle45;
	TCircle *Circle46;
	TCircle *Circle47;
	TCircle *Circle48;
	TCircle *Circle49;
	TCircle *Circle50;
	TCircle *Circle51;
	TCircle *Circle52;
	TCircle *Circle53;
	TCircle *Circle54;
	TCircle *Circle55;
	TCircle *Circle56;
	TCircle *Circle57;
	TCircle *Circle58;
	TCircle *Circle59;
	TCircle *Circle60;
	TCircle *Circle61;
	TCircle *Circle62;
	TCircle *Circle63;
	TCircle *Circle64;
	TPanel *Panel2;
	TLabel *Label1;
	TCircle *Circle65;
	TButton *Button2;
	TCircle *Circle66;
	TCircle *Circle67;
	TLabel *LabelBlanco;
	TLabel *LabelNegro;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TMediaPlayer *MediaPlayer1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Panel1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Panel1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  float X, float Y);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	Tablero tablero;
	void sincronizar(Tablero &_tablero);
	int tFicha;
    void jugarMaquina();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
