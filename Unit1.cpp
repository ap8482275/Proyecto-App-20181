/*
Programación II
Semestre 2018-1
Diego Solórzano - C.I. 18.678.679

Lenguaje de programación utilizado: C++
IDE de Programacion: Embarcadero RAD Studio Builder / Version: Berlin 10.1
*/

//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
#include <System.IOUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.LgXhdpiPh.fmx", _PLAT_ANDROID)

TForm1 *Form1;

void TForm1::jugarMaquina(){
	Sleep(2000);
	tablero.jugarMaquina();
	tablero.repintar();
	tablero.turno = !tablero.turno;
	LabelBlanco->Text = IntToStr(tablero.contar_blancas());
	LabelNegro->Text = IntToStr(tablero.contar_negras());
	if(tablero.turno == NEGRO)
		Circle65->Fill->Color = 0xFF000000;
	if(tablero.turno == BLANCO)
		Circle65->Fill->Color = 0xFFFFFFFF;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	Randomize();
	Panel1->Visible = false;
	Panel2->Visible = false;

	MediaPlayer1->Stop();
	#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) || defined(__ANDROID__)
	MediaPlayer1->FileName =
		IncludeTrailingPathDelimiter(System::Ioutils::TPath::GetDocumentsPath()) +
		"inicio.mp3";
	#else
		MediaPlayer1->FileName = "inicio.mp3";
	#endif
	MediaPlayer1->Play();

	Form1->Width = Screen->Width;
	Form1->Height = Screen->Height;
	Panel1->Width = Form1->Width;
	Panel1->Height = Form1->Width;
	Panel1->Position->X = 0;
	Panel2->Width = Form1->Width;
	Panel2->Position->X = 0;
	tFicha = Panel1->Width / 8;

	Button1->Width = Form1->Width / 2;
	Button1->Position->X = 0;
	Button1->Position->Y = Form1->Height - Button1->Height - 30;
	Button2->Width = Form1->Width / 2;
	Button2->Position->X = Button1->Position->X + Button1->Width;
	Button2->Position->Y = Form1->Height - Button2->Height - 30;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	//tFicha = 50;
	MediaPlayer1->Stop();

	sincronizar(tablero);
	tablero.set_tam(tFicha);
	tablero.inicializar();

	Panel1->Visible = true;
	Panel2->Visible = true;
	if(tablero.turno == NEGRO)
		Circle65->Fill->Color = 0xFF000000;
	if(tablero.turno == BLANCO)
		Circle65->Fill->Color = 0xFFFFFFFF;
	if(tablero.turno == -1)
		Circle65->Fill->Color = 0xFFE0E0E0;

	Label2->Visible = false;

	Application->ProcessMessages();
	if(tablero.turno == NEGRO){
		jugarMaquina();
	}

}
//---------------------------------------------------------------------------

void TForm1::sincronizar(Tablero &_tablero){
	int _f = 0;
	_tablero.fichas[_f++].elemento = Circle1;
	_tablero.fichas[_f++].elemento = Circle2;
	_tablero.fichas[_f++].elemento = Circle3;
	_tablero.fichas[_f++].elemento = Circle4;
	_tablero.fichas[_f++].elemento = Circle5;
	_tablero.fichas[_f++].elemento = Circle6;
	_tablero.fichas[_f++].elemento = Circle7;
	_tablero.fichas[_f++].elemento = Circle8;
	_tablero.fichas[_f++].elemento = Circle9;

	_tablero.fichas[_f++].elemento = Circle10;
	_tablero.fichas[_f++].elemento = Circle11;
	_tablero.fichas[_f++].elemento = Circle12;
	_tablero.fichas[_f++].elemento = Circle13;
	_tablero.fichas[_f++].elemento = Circle14;
	_tablero.fichas[_f++].elemento = Circle15;
	_tablero.fichas[_f++].elemento = Circle16;
	_tablero.fichas[_f++].elemento = Circle17;
	_tablero.fichas[_f++].elemento = Circle18;
	_tablero.fichas[_f++].elemento = Circle19;

	_tablero.fichas[_f++].elemento = Circle20;
	_tablero.fichas[_f++].elemento = Circle21;
	_tablero.fichas[_f++].elemento = Circle22;
	_tablero.fichas[_f++].elemento = Circle23;
	_tablero.fichas[_f++].elemento = Circle24;
	_tablero.fichas[_f++].elemento = Circle25;
	_tablero.fichas[_f++].elemento = Circle26;
	_tablero.fichas[_f++].elemento = Circle27;
	_tablero.fichas[_f++].elemento = Circle28;
	_tablero.fichas[_f++].elemento = Circle29;

	_tablero.fichas[_f++].elemento = Circle30;
	_tablero.fichas[_f++].elemento = Circle31;
	_tablero.fichas[_f++].elemento = Circle32;
	_tablero.fichas[_f++].elemento = Circle33;
	_tablero.fichas[_f++].elemento = Circle34;
	_tablero.fichas[_f++].elemento = Circle35;
	_tablero.fichas[_f++].elemento = Circle36;
	_tablero.fichas[_f++].elemento = Circle37;
	_tablero.fichas[_f++].elemento = Circle38;
	_tablero.fichas[_f++].elemento = Circle39;

	_tablero.fichas[_f++].elemento = Circle40;
	_tablero.fichas[_f++].elemento = Circle41;
	_tablero.fichas[_f++].elemento = Circle42;
	_tablero.fichas[_f++].elemento = Circle43;
	_tablero.fichas[_f++].elemento = Circle44;
	_tablero.fichas[_f++].elemento = Circle45;
	_tablero.fichas[_f++].elemento = Circle46;
	_tablero.fichas[_f++].elemento = Circle47;
	_tablero.fichas[_f++].elemento = Circle48;
	_tablero.fichas[_f++].elemento = Circle49;

	_tablero.fichas[_f++].elemento = Circle50;
	_tablero.fichas[_f++].elemento = Circle51;
	_tablero.fichas[_f++].elemento = Circle52;
	_tablero.fichas[_f++].elemento = Circle53;
	_tablero.fichas[_f++].elemento = Circle54;
	_tablero.fichas[_f++].elemento = Circle55;
	_tablero.fichas[_f++].elemento = Circle56;
	_tablero.fichas[_f++].elemento = Circle57;
	_tablero.fichas[_f++].elemento = Circle58;
	_tablero.fichas[_f++].elemento = Circle59;

	_tablero.fichas[_f++].elemento = Circle60;
	_tablero.fichas[_f++].elemento = Circle61;
	_tablero.fichas[_f++].elemento = Circle62;
	_tablero.fichas[_f++].elemento = Circle63;
	_tablero.fichas[_f++].elemento = Circle64;
}

void __fastcall TForm1::Panel1Click(TObject *Sender)
{
	/*TPoint p;
	GetCursorPos(&p);

	int offsetX, offsetY;
	offsetX = Form1->Left + Panel1->Position->X;
	offsetY = Form1->Top + Panel1->Position->Y;

	int posX, posY;
	posX = p.X - offsetX;
	posY = p.Y - offsetY;

	int _col = posX / tFicha;//posX = posX / tFicha;
	int _fil = posY / tFicha;//posY = posY / tFicha;

	if( (_fil >= 0 && _fil <= 7) && (_col >= 0 && _col <= 7) ){
		tablero.fichas[_fil*8 + _col].set_visible(true);
	}*/

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
    Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Panel1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y)
{
    int offsetX, offsetY;
	offsetX = /*Form1->Left + Panel1->Position->X;*/ 0;
	offsetY = /*Form1->Top + Panel1->Position->Y;*/ 0;

	int posX, posY;
	posX = X - offsetX;
	posY = Y - offsetY;

	int _col = posX / tFicha;//posX = posX / tFicha;
	int _fil = posY / tFicha;//posY = posY / tFicha;

	if( (_fil >= 0 && _fil <= 7) && (_col >= 0 && _col <= 7) ){
		if(tablero.validar_jugada(_fil,_col)){
			tablero.fichas[_fil*8 + _col].set_tipo(tablero.turno);
			tablero.fichas[_fil*8 + _col].set_visible(true);

			tablero.cambiar_fichas(_fil,_col);
            tablero.mapa[_fil][_col] = tablero.turno;
			tablero.repintar();
            tablero.turno = !tablero.turno;
		}
	}

	LabelBlanco->Text = IntToStr(tablero.contar_blancas());
	LabelNegro->Text = IntToStr(tablero.contar_negras());
	if(tablero.turno == NEGRO)
		Circle65->Fill->Color = 0xFF000000;
	if(tablero.turno == BLANCO)
		Circle65->Fill->Color = 0xFFFFFFFF;

    Application->ProcessMessages();

	if(tablero.gameOver()){
        Panel1->Visible = false;
		Label2->Visible = true;
		if(tablero.contar_blancas() > tablero.contar_negras())
			Label2->Text = "GANO EL JUGADOR BLANCO";
		if(tablero.contar_blancas() < tablero.contar_negras())
			Label2->Text = "GANO EL JUGADOR NEGRO";
		if(tablero.contar_blancas() == tablero.contar_negras())
			Label2->Text = "HAN EMPATADO";
	}else{
        if(tablero.turno == NEGRO){
			jugarMaquina();
		}
	}


}
//---------------------------------------------------------------------------

