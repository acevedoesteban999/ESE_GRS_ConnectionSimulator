#pragma once
#include "Connection.h"
#include <msclr\marshal.h>
Connection**c;
bool ErrorThWebSocketClient=false;
bool SalirThreadSinError=false;
bool CerrarCOM_Web=false;
void SelectThreadExtern()
{
	c[0]->Select();
}

void ThreadSocketClient()
{
	
	while(true)
	{
		char*toSend;
		toSend=c[2]->Recibir();
		if(toSend==NULL)
		{
			if(!c[2]->EstaConectado())
				return;
		}
		else
		{
			c[1]->Trasmitir(toSend);
		}
	}
}

void ThreadWebSocketClient()
{
	ErrorThWebSocketClient=SalirThreadSinError=CerrarCOM_Web=false;
	while(true)
	{
		try
		{
			char*toSend;
			toSend=c[1]->Recibir();
			if(toSend==NULL)
			{
				if(!c[1]->EstaConectado())
				{
					if(!SalirThreadSinError)
					{
						c[1]->CloseConnection();
						ErrorThWebSocketClient=true;
						c[0]->ActStatusClient(true);
						while(!SalirThreadSinError)
						{
							if(c[1]->inicializa((char*)string(c[1]->getChar()).c_str(),c[1]->getunsigned()))
							{
									char toSend[3];
									toSend[0]=(char)107;
									toSend[1]=(char)1;
									toSend[2]=0;
									c[1]->Trasmitir(toSend);
									fd_set descriptoresLectura;
									struct timeval tv;
									tv.tv_sec=3;
		 							tv.tv_usec=55555;
									FD_ZERO(&descriptoresLectura);
									FD_SET(c[1]->GetSocket(),&descriptoresLectura);
									select(c[1]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
									bool err=true;
									char*toReciv;
									if(FD_ISSET(c[1]->GetSocket(),&descriptoresLectura))
									{
										toReciv=c[1]->Recibir();
										if(toReciv!=NULL)
											if(toReciv[0]==(char)107)
				 							err=false;
									}
									if(err)
									{
										System::Windows::Forms::MessageBox::Show("Error al Reconectar a la Web");
										CerrarCOM_Web=true;
										c[0]->ActStatusClient(true);
										return;
									}
								toSend[0]=(char)99;
								c[1]->Trasmitir(toSend);
								FD_ZERO(&descriptoresLectura);
								FD_SET(c[1]->GetSocket(),&descriptoresLectura);
								select(c[1]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
								err=true;
								if(FD_ISSET(c[1]->GetSocket(),&descriptoresLectura))
								{
									toReciv=c[1]->Recibir();
									if(toReciv!=NULL)
										if(toReciv[0]==(char)99)
										{
											err=false;
											switch (toReciv[1])
											{
											case 4:
												if(c[0]->SocketServer_ClientUserIndex()!=-1)
												{
													System::Windows::Forms::MessageBox::Show("User perdido del ServerSocket");
													c[0]->SocketServer_QuitarOnlyUSER(c[0]->SocketServer_ClientUserIndex());
												}
												toSend[0]=(char)51;
												c[2]->Trasmitir(toSend);
												if(c[0]->SocketServer_ClientESEIndex()!=-1)
												{
													System::Windows::Forms::MessageBox::Show("ESE perdido del ServerSocket");
													c[0]->SocketServer_QuitarOnlyESE(c[0]->SocketServer_ClientESEIndex());
												}
												toSend[0]=(char)35;
												c[2]->Trasmitir(toSend);
												break;
											case 3:
												if(c[0]->SocketServer_ClientESEIndex()!=-1)
												{
													System::Windows::Forms::MessageBox::Show("ESE perdido del ServerSocket");
													c[0]->SocketServer_QuitarOnlyESE(c[0]->SocketServer_ClientESEIndex());
												}
												toSend[0]=(char)35;
												c[2]->Trasmitir(toSend);
												if(c[0]->SocketServer_ClientUserIndex()!=-1)
												{
													bool err1=true;
													toSend[0]=(char)51;
													c[1]->Trasmitir(toSend);
													FD_ZERO(&descriptoresLectura);
													FD_SET(c[1]->GetSocket(),&descriptoresLectura);
													select(c[1]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
													if(FD_ISSET(c[1]->GetSocket(),&descriptoresLectura))
													{
														toReciv=c[1]->Recibir();
														if(toReciv!=NULL)
															if(toReciv[0]==(char)51)
																err1=false;
													}
													if(err1)
													{
														System::Windows::Forms::MessageBox::Show("User perdido del ServerSocket");
														c[0]->SocketServer_QuitarOnlyUSER(c[0]->SocketServer_ClientUserIndex());
													}
												}
												break;
											case 2:
												if(c[0]->SocketServer_ClientUserIndex()!=-1)
												{
													System::Windows::Forms::MessageBox::Show("User perdido del ServerSocket");
													c[0]->SocketServer_QuitarOnlyUSER(c[0]->SocketServer_ClientUserIndex());
												}
												toSend[0]=(char)51;
												c[2]->Trasmitir(toSend);
												if(c[0]->SocketServer_ClientESEIndex()!=-1)
												{
													bool err1=true;
													toSend[0]=(char)35;
													c[1]->Trasmitir(toSend);
													FD_ZERO(&descriptoresLectura);
													FD_SET(c[1]->GetSocket(),&descriptoresLectura);
													select(c[1]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
													if(FD_ISSET(c[1]->GetSocket(),&descriptoresLectura))
													{
														toReciv=c[1]->Recibir();
														if(toReciv!=NULL)
															if(toReciv[0]==(char)35)
																err1=false;
													}
													if(err1)
													{
														System::Windows::Forms::MessageBox::Show("ESE perdido del ServerSocket");
														c[0]->SocketServer_QuitarOnlyESE(c[0]->SocketServer_ClientESEIndex());
													}
												}
												break;
											case 1:
												if(c[0]->SocketServer_ClientESEIndex()!=-1)
												{
													bool err1=true;
													toSend[0]=(char)35;
													c[1]->Trasmitir(toSend);
													FD_ZERO(&descriptoresLectura);
													FD_SET(c[1]->GetSocket(),&descriptoresLectura);
													select(c[1]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
													if(FD_ISSET(c[1]->GetSocket(),&descriptoresLectura))
													{
														toReciv=c[1]->Recibir();
														if(toReciv!=NULL)
															if(toReciv[0]==(char)35)
																err1=false;
													}
													if(err1)
													{
														System::Windows::Forms::MessageBox::Show("ESE perdido del ServerSocket");
														c[0]->SocketServer_QuitarOnlyESE(c[0]->SocketServer_ClientESEIndex());
													}
												}
												if(c[0]->SocketServer_ClientUserIndex()!=-1)
												{
													bool err1=true;
													toSend[0]=(char)51;
													c[1]->Trasmitir(toSend);
													FD_ZERO(&descriptoresLectura);
													FD_SET(c[1]->GetSocket(),&descriptoresLectura);
													select(c[1]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
													if(FD_ISSET(c[1]->GetSocket(),&descriptoresLectura))
													{
														toReciv=c[1]->Recibir();
														if(toReciv!=NULL)
															if(toReciv[0]==(char)51)
																err1=false;
													}
													if(err1)
													{
														System::Windows::Forms::MessageBox::Show("User perdido del ServerSocket");
														c[0]->SocketServer_QuitarOnlyUSER(c[0]->SocketServer_ClientUserIndex());
													}
												}
												break;
											}
										}
								}
								if(err)
								{
									System::Windows::Forms::MessageBox::Show("ERROR en la comunicacion SocketServer-Web");
									c[1]->CloseConnection();
									c[2]->CloseConnection();
									return;
								}
								//ErrorThWebSocketClient=true;
								//
								ErrorThWebSocketClient=false;
								c[0]->ActStatusClient(true);
								throw(true);
							}
						}
					}
					return;
				}
			}
			else
			{
				c[2]->Trasmitir(toSend);
			}
		}catch(bool)
		{
		}
	}	
}

void ThreadWeb()
{
	SalirThreadSinError=ErrorThWebSocketClient=CerrarCOM_Web=false;
	char*toReciv;
	while(true)
	{
		try
		{
			toReciv=c[0]->Recibir();
			if(toReciv==NULL)
			{
				if(!c[0]->EstaConectado())
				{
					if(!SalirThreadSinError)
					{
						c[0]->CloseConnection();
						ErrorThWebSocketClient=true;
						c[0]->ActStatusClient(true);
						while(!SalirThreadSinError)
						{
							if(c[0]->inicializa((char*)string(c[0]->getChar()).c_str(),c[0]->getunsigned()))
							{
								char toSend[3];
								toSend[0]=(char)35;
								toSend[1]=(char)1;
								toSend[2]=0;
								bool err=true;
								c[0]->Trasmitir(toSend);
								fd_set descriptoresLectura;
								struct timeval tv;
								tv.tv_sec=3;
		 						tv.tv_usec=55555;
								FD_ZERO(&descriptoresLectura);
								FD_SET(c[0]->GetSocket(),&descriptoresLectura);
								select(c[0]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
								if(FD_ISSET(c[0]->GetSocket(),&descriptoresLectura))
								{
									toReciv=c[0]->Recibir();
									if(toReciv!=NULL)
										if(toReciv[0]==(char)35)
											err=false;
								}
								if(err)
								{
									System::Windows::Forms::MessageBox::Show("Error al Reconectar a la Web");
									CerrarCOM_Web=true;
									c[0]->ActStatusClient(true);
									return;
								
								}
								ErrorThWebSocketClient=false;
								c[0]->ActStatusClient(true);
								throw(true);
							}
						}
					}
					return;
				}
			}
		}catch(bool){}
		
	}

}

namespace ESE_GRS_ConnectionSimulator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
	SOCKET s1,s2;	
	msclr::interop::marshal_context context;
	unsigned contClients,contVerif,contClienteVista;
	System::Threading::Thread^th,^thSocketCliente,^thWebSocketCliente;
	System::Threading::Mutex m1,m2,m3;
	bool VerifCOM,VerifSocket;
	bool COM,Socket_Cliente,COM_Soket,WebSocket,SocketServer,Web;
	unsigned contVistaCarga;
private: System::Windows::Forms::TabControl^  tabControl1;
private: System::Windows::Forms::TabPage^  tabPageCOM;
private: System::Windows::Forms::TabPage^  tabPagePuente;
private: System::Windows::Forms::TabPage^  tabPageSocket;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::TextBox^  textBoxCOMPuerto;
private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::Label^  labelCOM;
private: System::Windows::Forms::Button^  buttonCOMIniciar;
private: System::Windows::Forms::TextBox^  textBoxCOMVelocidad;
private: System::Windows::Forms::CheckBox^  checkBox1COMVelocidad;
private: System::Windows::Forms::CheckBox^  checkBox1COMPuerto;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Button^  buttonSocketIniciar;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::Label^  labelSocketServer;
private: System::Windows::Forms::TextBox^  textBoxSocketPuerto;
private: System::Windows::Forms::CheckBox^  checkBoxSocketPuerto;
private: System::Windows::Forms::CheckBox^  checkBoxSocketIP;
private: System::Windows::Forms::TabPage^  tabPageAbout;
private: System::Windows::Forms::Timer^  timer1;
private: System::Windows::Forms::CheckBox^  checkBoxSocketPuertoPuente;
private: System::Windows::Forms::CheckBox^  checkBoxSocketIPPuente;
private: System::Windows::Forms::CheckBox^  checkBoxCOMVelocidadPuente;
private: System::Windows::Forms::CheckBox^  checkBoxCOMPuertoPuente;
private: System::Windows::Forms::Label^  labelSocketPuertoPuente;
private: System::Windows::Forms::Label^  labelSocketIPPuente;
private: System::Windows::Forms::Label^  labelCOMVelocidadPuente;
private: System::Windows::Forms::Label^  labelCOMPuertoPuente;
private: System::Windows::Forms::TextBox^  textBoxSocketPuertoPuente;
private: System::Windows::Forms::TextBox^  textBoxCOMVelocidadPuente;
private: System::Windows::Forms::TextBox^  textBoxCOMPuertoPuente;
private: System::Windows::Forms::Label^  labelSocketPuente;
private: System::Windows::Forms::Label^  labelCOMPuente;
private: System::Windows::Forms::Label^  labelPuentePuente;
private: System::Windows::Forms::TabControl^  tabControl3;
private: System::Windows::Forms::TabPage^  tabPage2;
private: System::Windows::Forms::Button^  buttonInitConecctionPuente;
private: System::Windows::Forms::Timer^  timer2;
private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer1;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape2;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape1;
private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer2;
private: Microsoft::VisualBasic::PowerPacks::OvalShape^  ovalShape1;
private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer3;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape3;
private: System::Windows::Forms::Button^  buttonDesconectarPuente;
private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::Label^  labelSocketPuenteTabControl3;
private: System::Windows::Forms::Label^  labelCOMPuenteTabControl3;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^SignoCarga;
private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer4;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape19;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape18;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape17;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape16;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape15;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape14;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape13;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape12;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape11;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape10;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape9;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape8;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape7;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape6;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape4;
private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel2;
private: System::Windows::Forms::Label^  label5;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape21;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape20;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape24;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape23;
private: System::Windows::Forms::ComboBox^  comboBoxSocketIP;
private: System::Windows::Forms::ComboBox^  comboBoxSocketIPPuente;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape28;
private: System::Windows::Forms::TabPage^  tabPageSocketClientesTabControl2;
private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
private: System::Windows::Forms::Label^  labelSocketClientesTabControl2;
private: System::Windows::Forms::Button^  buttonDesconectar;
private: System::Windows::Forms::Button^  button30;
private: System::Windows::Forms::Button^  buttonAcceso;
private: System::Windows::Forms::Button^  button29;
private: System::Windows::Forms::Button^  button28;
private: System::Windows::Forms::Button^  button27;
private: System::Windows::Forms::Button^  button26;
private: System::Windows::Forms::Button^  button25;
private: System::Windows::Forms::Button^  button24;
private: System::Windows::Forms::Button^  button23;
private: System::Windows::Forms::Button^  button22;
private: System::Windows::Forms::Button^  button21;
private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::Label^  label8;
private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer7;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShapeClientes;
private: System::Windows::Forms::Label^  labelMostrarHost;
private: System::Windows::Forms::Button^  buttonDescanectarServerWeb;
private: System::Windows::Forms::Button^  buttonConnectarHost;
private: System::Windows::Forms::Label^  labelPuertoWeb;
private: System::Windows::Forms::Label^  labelHost;
private: System::Windows::Forms::Label^  label1ServerWeb;
private: System::Windows::Forms::TextBox^  textBoxHostPuerto;
private: System::Windows::Forms::ComboBox^  comboBoxHost;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape25;
private: System::Windows::Forms::TabPage^  tabPageSocketServerTabControl2;
private: System::Windows::Forms::Label^  labelSocketAddrTabControl2;
private: System::Windows::Forms::CheckBox^  textBoxSocketDrawTabControl2;
private: System::Windows::Forms::Button^  buttonSocketAceptFocusTabControl2;
private: System::Windows::Forms::Button^  buttonSocketFocusTabControl2;
private: System::Windows::Forms::CheckBox^  checkBoxSocketIPTabControl2;
private: System::Windows::Forms::CheckBox^  checkBoxSocketPuertoTabControl2;
private: System::Windows::Forms::Label^  labelSocketCOMServerTabControl2;
private: System::Windows::Forms::Button^  buttonSocketDisconectTabControl2;
private: System::Windows::Forms::TextBox^  textBoxSocketLowByteTabControl2;
private: System::Windows::Forms::Button^  buttonSocketCancelButtonTabControl2;
private: System::Windows::Forms::TextBox^  textBoxSocketHightByteTabControl2;
private: System::Windows::Forms::Button^  buttonSocketAceptButtonTabControl2;
private: System::Windows::Forms::Button^  buttonSocketEnviarTabControl2;
private: System::Windows::Forms::Button^  buttonSocketRedireccionarTabControl2;
private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer5;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape22;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape5;
private: System::Windows::Forms::TabControl^  tabControl2;
private: System::Windows::Forms::Button^  buttonNOAcceso;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape31;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape30;
private: System::Windows::Forms::TabPage^  tabPageWeb;
private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer8;
private: System::Windows::Forms::Timer^  timer3;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape26;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape27;
private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::TabPage^  tabPageSocketCliente;
private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::CheckBox^  checkBox2;
private: System::Windows::Forms::CheckBox^  checkBox1;


private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::Button^  button1;
private: System::Windows::Forms::ComboBox^  comboBox2;
private: System::Windows::Forms::ComboBox^  comboBox1;
private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer6;
private: Microsoft::VisualBasic::PowerPacks::LineShape^  lineShape1;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape32;
private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape29;


private: System::ComponentModel::IContainer^  components;
	public:		
		MyForm(void)
		{
			InitializeComponent();
			c=new Connection*[1]();
			contVerif=0;
			Web=COM=SocketServer=COM_Soket=WebSocket=Socket_Cliente=false;
			contVistaCarga=0;
			contClienteVista=0;
			VerifCOM=VerifSocket=true;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl2->Location = System::Drawing::Point(0, 0);
			this->tabControl3->Location = System::Drawing::Point(0, 0);
			this->MaximumSize = System::Drawing::Size(300, 300);
			this->MinimumSize = System::Drawing::Size(300, 300);
			this->ClientSize = System::Drawing::Size(300, 300);
			this->labelMostrarHost->Location = System::Drawing::Point(51, 71);
		    this->labelMostrarHost->Size = System::Drawing::Size(168, 72);
			//
			//TODO: Add the constructor code here
			//
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			delete th,thSocketCliente,thWebSocketCliente,m1,m2,m3;
			CerrarTodasConexiones();
			if (components)
			{
				delete components;
			}
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPageAbout = (gcnew System::Windows::Forms::TabPage());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->tabPageCOM = (gcnew System::Windows::Forms::TabPage());
			this->checkBox1COMVelocidad = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1COMPuerto = (gcnew System::Windows::Forms::CheckBox());
			this->labelCOM = (gcnew System::Windows::Forms::Label());
			this->buttonCOMIniciar = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBoxCOMVelocidad = (gcnew System::Windows::Forms::TextBox());
			this->textBoxCOMPuerto = (gcnew System::Windows::Forms::TextBox());
			this->shapeContainer2 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->rectangleShape21 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->ovalShape1 = (gcnew Microsoft::VisualBasic::PowerPacks::OvalShape());
			this->tabPageSocketCliente = (gcnew System::Windows::Forms::TabPage());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tabPagePuente = (gcnew System::Windows::Forms::TabPage());
			this->comboBoxSocketIPPuente = (gcnew System::Windows::Forms::ComboBox());
			this->buttonInitConecctionPuente = (gcnew System::Windows::Forms::Button());
			this->checkBoxSocketPuertoPuente = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxSocketIPPuente = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxCOMVelocidadPuente = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxCOMPuertoPuente = (gcnew System::Windows::Forms::CheckBox());
			this->labelSocketPuertoPuente = (gcnew System::Windows::Forms::Label());
			this->labelSocketIPPuente = (gcnew System::Windows::Forms::Label());
			this->labelCOMVelocidadPuente = (gcnew System::Windows::Forms::Label());
			this->labelCOMPuertoPuente = (gcnew System::Windows::Forms::Label());
			this->textBoxSocketPuertoPuente = (gcnew System::Windows::Forms::TextBox());
			this->textBoxCOMVelocidadPuente = (gcnew System::Windows::Forms::TextBox());
			this->textBoxCOMPuertoPuente = (gcnew System::Windows::Forms::TextBox());
			this->labelSocketPuente = (gcnew System::Windows::Forms::Label());
			this->labelCOMPuente = (gcnew System::Windows::Forms::Label());
			this->labelPuentePuente = (gcnew System::Windows::Forms::Label());
			this->shapeContainer1 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->rectangleShape26 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape2 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape1 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->tabPageSocket = (gcnew System::Windows::Forms::TabPage());
			this->comboBoxSocketIP = (gcnew System::Windows::Forms::ComboBox());
			this->checkBoxSocketPuerto = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxSocketIP = (gcnew System::Windows::Forms::CheckBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->buttonSocketIniciar = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->labelSocketServer = (gcnew System::Windows::Forms::Label());
			this->textBoxSocketPuerto = (gcnew System::Windows::Forms::TextBox());
			this->shapeContainer3 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->rectangleShape20 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape3 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->tabPageWeb = (gcnew System::Windows::Forms::TabPage());
			this->buttonConnectarHost = (gcnew System::Windows::Forms::Button());
			this->buttonDescanectarServerWeb = (gcnew System::Windows::Forms::Button());
			this->labelMostrarHost = (gcnew System::Windows::Forms::Label());
			this->label1ServerWeb = (gcnew System::Windows::Forms::Label());
			this->labelHost = (gcnew System::Windows::Forms::Label());
			this->comboBoxHost = (gcnew System::Windows::Forms::ComboBox());
			this->textBoxHostPuerto = (gcnew System::Windows::Forms::TextBox());
			this->labelPuertoWeb = (gcnew System::Windows::Forms::Label());
			this->shapeContainer8 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->rectangleShape27 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape25 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->tabControl3 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->labelSocketPuenteTabControl3 = (gcnew System::Windows::Forms::Label());
			this->labelCOMPuenteTabControl3 = (gcnew System::Windows::Forms::Label());
			this->buttonDesconectarPuente = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->shapeContainer4 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->rectangleShape28 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape24 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape23 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape19 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape18 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape17 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape16 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape15 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape14 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape13 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape12 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape11 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape10 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape9 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape8 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape7 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape6 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape4 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->tabPageSocketClientesTabControl2 = (gcnew System::Windows::Forms::TabPage());
			this->buttonNOAcceso = (gcnew System::Windows::Forms::Button());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->labelSocketClientesTabControl2 = (gcnew System::Windows::Forms::Label());
			this->buttonDesconectar = (gcnew System::Windows::Forms::Button());
			this->button30 = (gcnew System::Windows::Forms::Button());
			this->buttonAcceso = (gcnew System::Windows::Forms::Button());
			this->button29 = (gcnew System::Windows::Forms::Button());
			this->button28 = (gcnew System::Windows::Forms::Button());
			this->button27 = (gcnew System::Windows::Forms::Button());
			this->button26 = (gcnew System::Windows::Forms::Button());
			this->button25 = (gcnew System::Windows::Forms::Button());
			this->button24 = (gcnew System::Windows::Forms::Button());
			this->button23 = (gcnew System::Windows::Forms::Button());
			this->button22 = (gcnew System::Windows::Forms::Button());
			this->button21 = (gcnew System::Windows::Forms::Button());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->shapeContainer7 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->rectangleShape31 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape30 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShapeClientes = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->tabPageSocketServerTabControl2 = (gcnew System::Windows::Forms::TabPage());
			this->labelSocketAddrTabControl2 = (gcnew System::Windows::Forms::Label());
			this->textBoxSocketDrawTabControl2 = (gcnew System::Windows::Forms::CheckBox());
			this->buttonSocketAceptFocusTabControl2 = (gcnew System::Windows::Forms::Button());
			this->buttonSocketFocusTabControl2 = (gcnew System::Windows::Forms::Button());
			this->checkBoxSocketIPTabControl2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxSocketPuertoTabControl2 = (gcnew System::Windows::Forms::CheckBox());
			this->labelSocketCOMServerTabControl2 = (gcnew System::Windows::Forms::Label());
			this->buttonSocketDisconectTabControl2 = (gcnew System::Windows::Forms::Button());
			this->textBoxSocketLowByteTabControl2 = (gcnew System::Windows::Forms::TextBox());
			this->buttonSocketCancelButtonTabControl2 = (gcnew System::Windows::Forms::Button());
			this->textBoxSocketHightByteTabControl2 = (gcnew System::Windows::Forms::TextBox());
			this->buttonSocketAceptButtonTabControl2 = (gcnew System::Windows::Forms::Button());
			this->buttonSocketEnviarTabControl2 = (gcnew System::Windows::Forms::Button());
			this->buttonSocketRedireccionarTabControl2 = (gcnew System::Windows::Forms::Button());
			this->shapeContainer5 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->rectangleShape22 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->rectangleShape5 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->tabControl2 = (gcnew System::Windows::Forms::TabControl());
			this->timer3 = (gcnew System::Windows::Forms::Timer(this->components));
			this->rectangleShape29 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->shapeContainer6 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->rectangleShape32 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->lineShape1 = (gcnew Microsoft::VisualBasic::PowerPacks::LineShape());
			this->tabControl1->SuspendLayout();
			this->tabPageAbout->SuspendLayout();
			this->flowLayoutPanel2->SuspendLayout();
			this->tabPageCOM->SuspendLayout();
			this->tabPageSocketCliente->SuspendLayout();
			this->tabPagePuente->SuspendLayout();
			this->tabPageSocket->SuspendLayout();
			this->tabPageWeb->SuspendLayout();
			this->tabControl3->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPageSocketClientesTabControl2->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->tabPageSocketServerTabControl2->SuspendLayout();
			this->tabControl2->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPageAbout);
			this->tabControl1->Controls->Add(this->tabPageCOM);
			this->tabControl1->Controls->Add(this->tabPageSocketCliente);
			this->tabControl1->Controls->Add(this->tabPagePuente);
			this->tabControl1->Controls->Add(this->tabPageSocket);
			this->tabControl1->Controls->Add(this->tabPageWeb);
			this->tabControl1->Location = System::Drawing::Point(300, 30);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(290, 264);
			this->tabControl1->TabIndex = 0;
			// 
			// tabPageAbout
			// 
			this->tabPageAbout->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->tabPageAbout->Controls->Add(this->label1);
			this->tabPageAbout->Controls->Add(this->flowLayoutPanel2);
			this->tabPageAbout->Location = System::Drawing::Point(4, 22);
			this->tabPageAbout->Name = L"tabPageAbout";
			this->tabPageAbout->Padding = System::Windows::Forms::Padding(3);
			this->tabPageAbout->Size = System::Drawing::Size(282, 238);
			this->tabPageAbout->TabIndex = 3;
			this->tabPageAbout->Text = L"ESE_info";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::White;
			this->label1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label1->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(20, 18);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(235, 27);
			this->label1->TabIndex = 1;
			this->label1->Text = L"ESE_GRS-Simulador";
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->BackColor = System::Drawing::Color::White;
			this->flowLayoutPanel2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->flowLayoutPanel2->Controls->Add(this->label5);
			this->flowLayoutPanel2->Controls->Add(this->label10);
			this->flowLayoutPanel2->Location = System::Drawing::Point(8, 63);
			this->flowLayoutPanel2->Margin = System::Windows::Forms::Padding(0);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Padding = System::Windows::Forms::Padding(0, 3, 0, 0);
			this->flowLayoutPanel2->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->flowLayoutPanel2->Size = System::Drawing::Size(258, 156);
			this->flowLayoutPanel2->TabIndex = 13;
			// 
			// label5
			// 
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(3, 3);
			this->label5->Name = L"label5";
			this->label5->Padding = System::Windows::Forms::Padding(0, 5, 0, 0);
			this->label5->Size = System::Drawing::Size(253, 120);
			this->label5->TabIndex = 2;
			this->label5->Text = L" \r\nSimulador del brazo ESE_GRS que \r\npermite crear un servidor por Sockets y\r\n un" 
				L" puente COM-SOCKET para \r\nmanipular varios clientes a la vez.\r\n\r\n\r\n\r\n \r\n  ";
			this->label5->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			// 
			// label10
			// 
			this->label10->BackColor = System::Drawing::Color::Transparent;
			this->label10->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(3, 123);
			this->label10->Name = L"label10";
			this->label10->Padding = System::Windows::Forms::Padding(0, 5, 0, 0);
			this->label10->Size = System::Drawing::Size(253, 50);
			this->label10->TabIndex = 3;
			this->label10->Text = L" v-4.3\r\n\r\n\r\n\r\n \r\n  ";
			this->label10->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// tabPageCOM
			// 
			this->tabPageCOM->BackColor = System::Drawing::Color::OrangeRed;
			this->tabPageCOM->Controls->Add(this->checkBox1COMVelocidad);
			this->tabPageCOM->Controls->Add(this->checkBox1COMPuerto);
			this->tabPageCOM->Controls->Add(this->labelCOM);
			this->tabPageCOM->Controls->Add(this->buttonCOMIniciar);
			this->tabPageCOM->Controls->Add(this->label3);
			this->tabPageCOM->Controls->Add(this->label2);
			this->tabPageCOM->Controls->Add(this->textBoxCOMVelocidad);
			this->tabPageCOM->Controls->Add(this->textBoxCOMPuerto);
			this->tabPageCOM->Controls->Add(this->shapeContainer2);
			this->tabPageCOM->ForeColor = System::Drawing::SystemColors::ControlText;
			this->tabPageCOM->Location = System::Drawing::Point(4, 22);
			this->tabPageCOM->Name = L"tabPageCOM";
			this->tabPageCOM->Padding = System::Windows::Forms::Padding(3);
			this->tabPageCOM->Size = System::Drawing::Size(282, 238);
			this->tabPageCOM->TabIndex = 0;
			this->tabPageCOM->Text = L"COM";
			// 
			// checkBox1COMVelocidad
			// 
			this->checkBox1COMVelocidad->AutoSize = true;
			this->checkBox1COMVelocidad->BackColor = System::Drawing::Color::Green;
			this->checkBox1COMVelocidad->Checked = true;
			this->checkBox1COMVelocidad->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1COMVelocidad->Cursor = System::Windows::Forms::Cursors::No;
			this->checkBox1COMVelocidad->Location = System::Drawing::Point(216, 143);
			this->checkBox1COMVelocidad->Name = L"checkBox1COMVelocidad";
			this->checkBox1COMVelocidad->Size = System::Drawing::Size(15, 14);
			this->checkBox1COMVelocidad->TabIndex = 8;
			this->checkBox1COMVelocidad->UseVisualStyleBackColor = false;
			this->checkBox1COMVelocidad->Click += gcnew System::EventHandler(this, &MyForm::checkBoxCOMVelocidad_Click);
			// 
			// checkBox1COMPuerto
			// 
			this->checkBox1COMPuerto->AutoSize = true;
			this->checkBox1COMPuerto->BackColor = System::Drawing::Color::Green;
			this->checkBox1COMPuerto->Checked = true;
			this->checkBox1COMPuerto->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1COMPuerto->Cursor = System::Windows::Forms::Cursors::No;
			this->checkBox1COMPuerto->ForeColor = System::Drawing::Color::Black;
			this->checkBox1COMPuerto->Location = System::Drawing::Point(216, 101);
			this->checkBox1COMPuerto->Name = L"checkBox1COMPuerto";
			this->checkBox1COMPuerto->Size = System::Drawing::Size(15, 14);
			this->checkBox1COMPuerto->TabIndex = 7;
			this->checkBox1COMPuerto->UseVisualStyleBackColor = false;
			this->checkBox1COMPuerto->Click += gcnew System::EventHandler(this, &MyForm::checkBoxCOMPuerto_Click);
			// 
			// labelCOM
			// 
			this->labelCOM->AutoSize = true;
			this->labelCOM->BackColor = System::Drawing::Color::White;
			this->labelCOM->Font = (gcnew System::Drawing::Font(L"Arial Rounded MT Bold", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->labelCOM->Location = System::Drawing::Point(81, 31);
			this->labelCOM->Name = L"labelCOM";
			this->labelCOM->Size = System::Drawing::Size(129, 22);
			this->labelCOM->TabIndex = 5;
			this->labelCOM->Text = L"Puerto Serie ";
			// 
			// buttonCOMIniciar
			// 
			this->buttonCOMIniciar->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonCOMIniciar->Location = System::Drawing::Point(85, 183);
			this->buttonCOMIniciar->Name = L"buttonCOMIniciar";
			this->buttonCOMIniciar->Size = System::Drawing::Size(112, 23);
			this->buttonCOMIniciar->TabIndex = 4;
			this->buttonCOMIniciar->Text = L"Conectar";
			this->buttonCOMIniciar->UseVisualStyleBackColor = true;
			this->buttonCOMIniciar->Click += gcnew System::EventHandler(this, &MyForm::ButtonIniciarConnection_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(37, 144);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(54, 13);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Velocidad";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(53, 106);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(38, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Puerto";
			// 
			// textBoxCOMVelocidad
			// 
			this->textBoxCOMVelocidad->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(5) {L"COM1\t", L"COM2", 
				L"COM3", L"COM4", L"COM5"});
			this->textBoxCOMVelocidad->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBoxCOMVelocidad->Location = System::Drawing::Point(110, 140);
			this->textBoxCOMVelocidad->Name = L"textBoxCOMVelocidad";
			this->textBoxCOMVelocidad->Size = System::Drawing::Size(87, 21);
			this->textBoxCOMVelocidad->TabIndex = 1;
			this->textBoxCOMVelocidad->Text = L"115200";
			this->textBoxCOMVelocidad->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxCOMIniciarConnection_TextChanged);
			// 
			// textBoxCOMPuerto
			// 
			this->textBoxCOMPuerto->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBoxCOMPuerto->ForeColor = System::Drawing::SystemColors::WindowText;
			this->textBoxCOMPuerto->Location = System::Drawing::Point(110, 101);
			this->textBoxCOMPuerto->Name = L"textBoxCOMPuerto";
			this->textBoxCOMPuerto->Size = System::Drawing::Size(87, 21);
			this->textBoxCOMPuerto->TabIndex = 0;
			this->textBoxCOMPuerto->Text = L"COM2";
			this->textBoxCOMPuerto->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxCOMIniciarConnection_TextChanged);
			// 
			// shapeContainer2
			// 
			this->shapeContainer2->Location = System::Drawing::Point(3, 3);
			this->shapeContainer2->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer2->Name = L"shapeContainer2";
			this->shapeContainer2->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(2) {this->rectangleShape21, 
				this->ovalShape1});
			this->shapeContainer2->Size = System::Drawing::Size(276, 232);
			this->shapeContainer2->TabIndex = 9;
			this->shapeContainer2->TabStop = false;
			// 
			// rectangleShape21
			// 
			this->rectangleShape21->BackColor = System::Drawing::Color::White;
			this->rectangleShape21->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape21->Location = System::Drawing::Point(28, 77);
			this->rectangleShape21->Name = L"rectangleShape21";
			this->rectangleShape21->Size = System::Drawing::Size(216, 137);
			// 
			// ovalShape1
			// 
			this->ovalShape1->BackColor = System::Drawing::Color::White;
			this->ovalShape1->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->ovalShape1->Location = System::Drawing::Point(54, 9);
			this->ovalShape1->Name = L"ovalShape1";
			this->ovalShape1->Size = System::Drawing::Size(166, 62);
			// 
			// tabPageSocketCliente
			// 
			this->tabPageSocketCliente->BackColor = System::Drawing::Color::Coral;
			this->tabPageSocketCliente->Controls->Add(this->comboBox2);
			this->tabPageSocketCliente->Controls->Add(this->comboBox1);
			this->tabPageSocketCliente->Controls->Add(this->label13);
			this->tabPageSocketCliente->Controls->Add(this->checkBox2);
			this->tabPageSocketCliente->Controls->Add(this->checkBox1);
			this->tabPageSocketCliente->Controls->Add(this->label12);
			this->tabPageSocketCliente->Controls->Add(this->label11);
			this->tabPageSocketCliente->Controls->Add(this->button1);
			this->tabPageSocketCliente->Controls->Add(this->shapeContainer6);
			this->tabPageSocketCliente->Location = System::Drawing::Point(4, 22);
			this->tabPageSocketCliente->Name = L"tabPageSocketCliente";
			this->tabPageSocketCliente->Padding = System::Windows::Forms::Padding(3);
			this->tabPageSocketCliente->Size = System::Drawing::Size(282, 238);
			this->tabPageSocketCliente->TabIndex = 5;
			this->tabPageSocketCliente->Text = L"S.Cliente";
			// 
			// comboBox2
			// 
			this->comboBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(95, 130);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(107, 24);
			this->comboBox2->TabIndex = 9;
			this->comboBox2->Text = L"55555";
			this->comboBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(95, 86);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(107, 24);
			this->comboBox1->TabIndex = 8;
			this->comboBox1->Text = L"127.0.0.1";
			this->comboBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// label13
			// 
			this->label13->BackColor = System::Drawing::Color::White;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label13->Location = System::Drawing::Point(21, 91);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(54, 18);
			this->label13->TabIndex = 7;
			this->label13->Text = L"Ip";
			this->label13->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->checkBox2->Checked = true;
			this->checkBox2->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox2->Location = System::Drawing::Point(208, 137);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(15, 14);
			this->checkBox2->TabIndex = 6;
			this->checkBox2->UseVisualStyleBackColor = false;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->checkBox1->Location = System::Drawing::Point(208, 90);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(15, 14);
			this->checkBox1->TabIndex = 5;
			this->checkBox1->UseVisualStyleBackColor = false;
			// 
			// label12
			// 
			this->label12->BackColor = System::Drawing::Color::White;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(21, 130);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(55, 21);
			this->label12->TabIndex = 2;
			this->label12->Text = L"Puerto";
			this->label12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->BackColor = System::Drawing::Color::White;
			this->label11->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(20, 28);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(239, 32);
			this->label11->TabIndex = 1;
			this->label11->Text = L"Socket_Cliente";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(95, 183);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(96, 36);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Conectar";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::ButtonIniciarConnection_Click);
			// 
			// tabPagePuente
			// 
			this->tabPagePuente->BackColor = System::Drawing::Color::LawnGreen;
			this->tabPagePuente->Controls->Add(this->comboBoxSocketIPPuente);
			this->tabPagePuente->Controls->Add(this->buttonInitConecctionPuente);
			this->tabPagePuente->Controls->Add(this->checkBoxSocketPuertoPuente);
			this->tabPagePuente->Controls->Add(this->checkBoxSocketIPPuente);
			this->tabPagePuente->Controls->Add(this->checkBoxCOMVelocidadPuente);
			this->tabPagePuente->Controls->Add(this->checkBoxCOMPuertoPuente);
			this->tabPagePuente->Controls->Add(this->labelSocketPuertoPuente);
			this->tabPagePuente->Controls->Add(this->labelSocketIPPuente);
			this->tabPagePuente->Controls->Add(this->labelCOMVelocidadPuente);
			this->tabPagePuente->Controls->Add(this->labelCOMPuertoPuente);
			this->tabPagePuente->Controls->Add(this->textBoxSocketPuertoPuente);
			this->tabPagePuente->Controls->Add(this->textBoxCOMVelocidadPuente);
			this->tabPagePuente->Controls->Add(this->textBoxCOMPuertoPuente);
			this->tabPagePuente->Controls->Add(this->labelSocketPuente);
			this->tabPagePuente->Controls->Add(this->labelCOMPuente);
			this->tabPagePuente->Controls->Add(this->labelPuentePuente);
			this->tabPagePuente->Controls->Add(this->shapeContainer1);
			this->tabPagePuente->Location = System::Drawing::Point(4, 22);
			this->tabPagePuente->Name = L"tabPagePuente";
			this->tabPagePuente->Padding = System::Windows::Forms::Padding(3);
			this->tabPagePuente->Size = System::Drawing::Size(282, 238);
			this->tabPagePuente->TabIndex = 1;
			this->tabPagePuente->Tag = L"";
			this->tabPagePuente->Text = L"P.COM";
			// 
			// comboBoxSocketIPPuente
			// 
			this->comboBoxSocketIPPuente->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->comboBoxSocketIPPuente->FormattingEnabled = true;
			this->comboBoxSocketIPPuente->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"INADDR_ANY", L"127.0.0.1"});
			this->comboBoxSocketIPPuente->Location = System::Drawing::Point(165, 110);
			this->comboBoxSocketIPPuente->Name = L"comboBoxSocketIPPuente";
			this->comboBoxSocketIPPuente->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->comboBoxSocketIPPuente->Size = System::Drawing::Size(96, 22);
			this->comboBoxSocketIPPuente->TabIndex = 19;
			this->comboBoxSocketIPPuente->Text = L"INADDR_ANY";
			this->comboBoxSocketIPPuente->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxSocketPuente_TextChanged);
			// 
			// buttonInitConecctionPuente
			// 
			this->buttonInitConecctionPuente->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonInitConecctionPuente->Location = System::Drawing::Point(80, 204);
			this->buttonInitConecctionPuente->Name = L"buttonInitConecctionPuente";
			this->buttonInitConecctionPuente->Size = System::Drawing::Size(109, 23);
			this->buttonInitConecctionPuente->TabIndex = 17;
			this->buttonInitConecctionPuente->Text = L"Iniciar";
			this->buttonInitConecctionPuente->UseVisualStyleBackColor = true;
			this->buttonInitConecctionPuente->Click += gcnew System::EventHandler(this, &MyForm::buttonInitConecctionPuente_Click);
			// 
			// checkBoxSocketPuertoPuente
			// 
			this->checkBoxSocketPuertoPuente->AutoSize = true;
			this->checkBoxSocketPuertoPuente->BackColor = System::Drawing::Color::Green;
			this->checkBoxSocketPuertoPuente->Checked = true;
			this->checkBoxSocketPuertoPuente->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxSocketPuertoPuente->Cursor = System::Windows::Forms::Cursors::No;
			this->checkBoxSocketPuertoPuente->Location = System::Drawing::Point(144, 158);
			this->checkBoxSocketPuertoPuente->Name = L"checkBoxSocketPuertoPuente";
			this->checkBoxSocketPuertoPuente->Size = System::Drawing::Size(15, 14);
			this->checkBoxSocketPuertoPuente->TabIndex = 16;
			this->checkBoxSocketPuertoPuente->UseVisualStyleBackColor = false;
			this->checkBoxSocketPuertoPuente->Click += gcnew System::EventHandler(this, &MyForm::checkBoxSocketPuertoPuente_Click);
			// 
			// checkBoxSocketIPPuente
			// 
			this->checkBoxSocketIPPuente->AutoSize = true;
			this->checkBoxSocketIPPuente->BackColor = System::Drawing::Color::Green;
			this->checkBoxSocketIPPuente->Checked = true;
			this->checkBoxSocketIPPuente->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxSocketIPPuente->Cursor = System::Windows::Forms::Cursors::No;
			this->checkBoxSocketIPPuente->Location = System::Drawing::Point(144, 114);
			this->checkBoxSocketIPPuente->Name = L"checkBoxSocketIPPuente";
			this->checkBoxSocketIPPuente->Size = System::Drawing::Size(15, 14);
			this->checkBoxSocketIPPuente->TabIndex = 15;
			this->checkBoxSocketIPPuente->UseVisualStyleBackColor = false;
			this->checkBoxSocketIPPuente->Click += gcnew System::EventHandler(this, &MyForm::checkBoxSocketIPPuente_Click);
			// 
			// checkBoxCOMVelocidadPuente
			// 
			this->checkBoxCOMVelocidadPuente->AutoSize = true;
			this->checkBoxCOMVelocidadPuente->BackColor = System::Drawing::Color::Green;
			this->checkBoxCOMVelocidadPuente->Checked = true;
			this->checkBoxCOMVelocidadPuente->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxCOMVelocidadPuente->Cursor = System::Windows::Forms::Cursors::No;
			this->checkBoxCOMVelocidadPuente->Location = System::Drawing::Point(119, 158);
			this->checkBoxCOMVelocidadPuente->Name = L"checkBoxCOMVelocidadPuente";
			this->checkBoxCOMVelocidadPuente->Size = System::Drawing::Size(15, 14);
			this->checkBoxCOMVelocidadPuente->TabIndex = 14;
			this->checkBoxCOMVelocidadPuente->UseVisualStyleBackColor = false;
			this->checkBoxCOMVelocidadPuente->Click += gcnew System::EventHandler(this, &MyForm::checkBoxCOMVelocidadPuente_Click);
			// 
			// checkBoxCOMPuertoPuente
			// 
			this->checkBoxCOMPuertoPuente->AutoSize = true;
			this->checkBoxCOMPuertoPuente->BackColor = System::Drawing::Color::Green;
			this->checkBoxCOMPuertoPuente->Checked = true;
			this->checkBoxCOMPuertoPuente->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxCOMPuertoPuente->Cursor = System::Windows::Forms::Cursors::No;
			this->checkBoxCOMPuertoPuente->Location = System::Drawing::Point(119, 114);
			this->checkBoxCOMPuertoPuente->Name = L"checkBoxCOMPuertoPuente";
			this->checkBoxCOMPuertoPuente->Size = System::Drawing::Size(15, 14);
			this->checkBoxCOMPuertoPuente->TabIndex = 13;
			this->checkBoxCOMPuertoPuente->UseVisualStyleBackColor = false;
			this->checkBoxCOMPuertoPuente->Click += gcnew System::EventHandler(this, &MyForm::checkBoxCOMPuertoPuente_Click);
			// 
			// labelSocketPuertoPuente
			// 
			this->labelSocketPuertoPuente->AutoSize = true;
			this->labelSocketPuertoPuente->BackColor = System::Drawing::Color::White;
			this->labelSocketPuertoPuente->Location = System::Drawing::Point(194, 138);
			this->labelSocketPuertoPuente->Name = L"labelSocketPuertoPuente";
			this->labelSocketPuertoPuente->Size = System::Drawing::Size(38, 13);
			this->labelSocketPuertoPuente->TabIndex = 12;
			this->labelSocketPuertoPuente->Text = L"Puerto";
			// 
			// labelSocketIPPuente
			// 
			this->labelSocketIPPuente->AutoSize = true;
			this->labelSocketIPPuente->BackColor = System::Drawing::Color::White;
			this->labelSocketIPPuente->Location = System::Drawing::Point(205, 91);
			this->labelSocketIPPuente->Name = L"labelSocketIPPuente";
			this->labelSocketIPPuente->Size = System::Drawing::Size(17, 13);
			this->labelSocketIPPuente->TabIndex = 11;
			this->labelSocketIPPuente->Text = L"IP";
			// 
			// labelCOMVelocidadPuente
			// 
			this->labelCOMVelocidadPuente->AutoSize = true;
			this->labelCOMVelocidadPuente->BackColor = System::Drawing::Color::White;
			this->labelCOMVelocidadPuente->Location = System::Drawing::Point(37, 134);
			this->labelCOMVelocidadPuente->Name = L"labelCOMVelocidadPuente";
			this->labelCOMVelocidadPuente->Size = System::Drawing::Size(54, 13);
			this->labelCOMVelocidadPuente->TabIndex = 10;
			this->labelCOMVelocidadPuente->Text = L"Velocidad";
			// 
			// labelCOMPuertoPuente
			// 
			this->labelCOMPuertoPuente->AutoSize = true;
			this->labelCOMPuertoPuente->BackColor = System::Drawing::Color::White;
			this->labelCOMPuertoPuente->Location = System::Drawing::Point(51, 91);
			this->labelCOMPuertoPuente->Name = L"labelCOMPuertoPuente";
			this->labelCOMPuertoPuente->Size = System::Drawing::Size(38, 13);
			this->labelCOMPuertoPuente->TabIndex = 9;
			this->labelCOMPuertoPuente->Text = L"Puerto";
			// 
			// textBoxSocketPuertoPuente
			// 
			this->textBoxSocketPuertoPuente->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->textBoxSocketPuertoPuente->Location = System::Drawing::Point(165, 155);
			this->textBoxSocketPuertoPuente->Name = L"textBoxSocketPuertoPuente";
			this->textBoxSocketPuertoPuente->Size = System::Drawing::Size(91, 21);
			this->textBoxSocketPuertoPuente->TabIndex = 8;
			this->textBoxSocketPuertoPuente->Text = L"55555";
			this->textBoxSocketPuertoPuente->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBoxSocketPuertoPuente->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxSocketPuente_TextChanged);
			// 
			// textBoxCOMVelocidadPuente
			// 
			this->textBoxCOMVelocidadPuente->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->textBoxCOMVelocidadPuente->Location = System::Drawing::Point(19, 154);
			this->textBoxCOMVelocidadPuente->Name = L"textBoxCOMVelocidadPuente";
			this->textBoxCOMVelocidadPuente->Size = System::Drawing::Size(94, 21);
			this->textBoxCOMVelocidadPuente->TabIndex = 6;
			this->textBoxCOMVelocidadPuente->Text = L"115200";
			this->textBoxCOMVelocidadPuente->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBoxCOMVelocidadPuente->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxCOMPuente_TextChanged);
			// 
			// textBoxCOMPuertoPuente
			// 
			this->textBoxCOMPuertoPuente->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->textBoxCOMPuertoPuente->Location = System::Drawing::Point(19, 111);
			this->textBoxCOMPuertoPuente->Name = L"textBoxCOMPuertoPuente";
			this->textBoxCOMPuertoPuente->Size = System::Drawing::Size(94, 21);
			this->textBoxCOMPuertoPuente->TabIndex = 5;
			this->textBoxCOMPuertoPuente->Text = L"COM2";
			this->textBoxCOMPuertoPuente->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBoxCOMPuertoPuente->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxCOMPuente_TextChanged);
			// 
			// labelSocketPuente
			// 
			this->labelSocketPuente->AutoSize = true;
			this->labelSocketPuente->BackColor = System::Drawing::Color::White;
			this->labelSocketPuente->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->labelSocketPuente->Location = System::Drawing::Point(171, 58);
			this->labelSocketPuente->Name = L"labelSocketPuente";
			this->labelSocketPuente->Size = System::Drawing::Size(73, 24);
			this->labelSocketPuente->TabIndex = 4;
			this->labelSocketPuente->Text = L"Socket";
			// 
			// labelCOMPuente
			// 
			this->labelCOMPuente->AutoSize = true;
			this->labelCOMPuente->BackColor = System::Drawing::Color::White;
			this->labelCOMPuente->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->labelCOMPuente->Location = System::Drawing::Point(48, 59);
			this->labelCOMPuente->Name = L"labelCOMPuente";
			this->labelCOMPuente->Size = System::Drawing::Size(43, 22);
			this->labelCOMPuente->TabIndex = 3;
			this->labelCOMPuente->Text = L"COM";
			// 
			// labelPuentePuente
			// 
			this->labelPuentePuente->AutoSize = true;
			this->labelPuentePuente->BackColor = System::Drawing::Color::LawnGreen;
			this->labelPuentePuente->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->labelPuentePuente->Location = System::Drawing::Point(65, 10);
			this->labelPuentePuente->Name = L"labelPuentePuente";
			this->labelPuentePuente->Size = System::Drawing::Size(147, 25);
			this->labelPuentePuente->TabIndex = 2;
			this->labelPuentePuente->Text = L"Puente COM";
			// 
			// shapeContainer1
			// 
			this->shapeContainer1->Location = System::Drawing::Point(3, 3);
			this->shapeContainer1->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer1->Name = L"shapeContainer1";
			this->shapeContainer1->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(3) {this->rectangleShape26, 
				this->rectangleShape2, this->rectangleShape1});
			this->shapeContainer1->Size = System::Drawing::Size(276, 232);
			this->shapeContainer1->TabIndex = 18;
			this->shapeContainer1->TabStop = false;
			// 
			// rectangleShape26
			// 
			this->rectangleShape26->BackColor = System::Drawing::Color::LawnGreen;
			this->rectangleShape26->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape26->Location = System::Drawing::Point(49, 2);
			this->rectangleShape26->Name = L"rectangleShape26";
			this->rectangleShape26->Size = System::Drawing::Size(175, 37);
			// 
			// rectangleShape2
			// 
			this->rectangleShape2->BackColor = System::Drawing::Color::White;
			this->rectangleShape2->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape2->Location = System::Drawing::Point(137, 45);
			this->rectangleShape2->Name = L"rectangleShape2";
			this->rectangleShape2->Size = System::Drawing::Size(125, 148);
			// 
			// rectangleShape1
			// 
			this->rectangleShape1->BackColor = System::Drawing::Color::White;
			this->rectangleShape1->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape1->Location = System::Drawing::Point(5, 45);
			this->rectangleShape1->Name = L"rectangleShape1";
			this->rectangleShape1->Size = System::Drawing::Size(128, 147);
			// 
			// tabPageSocket
			// 
			this->tabPageSocket->BackColor = System::Drawing::Color::DimGray;
			this->tabPageSocket->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->tabPageSocket->Controls->Add(this->comboBoxSocketIP);
			this->tabPageSocket->Controls->Add(this->checkBoxSocketPuerto);
			this->tabPageSocket->Controls->Add(this->checkBoxSocketIP);
			this->tabPageSocket->Controls->Add(this->label7);
			this->tabPageSocket->Controls->Add(this->buttonSocketIniciar);
			this->tabPageSocket->Controls->Add(this->label6);
			this->tabPageSocket->Controls->Add(this->labelSocketServer);
			this->tabPageSocket->Controls->Add(this->textBoxSocketPuerto);
			this->tabPageSocket->Controls->Add(this->shapeContainer3);
			this->tabPageSocket->Location = System::Drawing::Point(4, 22);
			this->tabPageSocket->Name = L"tabPageSocket";
			this->tabPageSocket->Padding = System::Windows::Forms::Padding(3);
			this->tabPageSocket->Size = System::Drawing::Size(282, 238);
			this->tabPageSocket->TabIndex = 2;
			this->tabPageSocket->Text = L"P.WEB";
			// 
			// comboBoxSocketIP
			// 
			this->comboBoxSocketIP->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->comboBoxSocketIP->FormattingEnabled = true;
			this->comboBoxSocketIP->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"INADDR_ANY", L"127.0.0.1"});
			this->comboBoxSocketIP->Location = System::Drawing::Point(84, 100);
			this->comboBoxSocketIP->Name = L"comboBoxSocketIP";
			this->comboBoxSocketIP->Size = System::Drawing::Size(95, 22);
			this->comboBoxSocketIP->TabIndex = 11;
			this->comboBoxSocketIP->Text = L"INADDR_ANY";
			this->comboBoxSocketIP->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxSocketIniciarConnection_TextChanged);
			// 
			// checkBoxSocketPuerto
			// 
			this->checkBoxSocketPuerto->AutoSize = true;
			this->checkBoxSocketPuerto->BackColor = System::Drawing::Color::Green;
			this->checkBoxSocketPuerto->Checked = true;
			this->checkBoxSocketPuerto->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxSocketPuerto->Cursor = System::Windows::Forms::Cursors::No;
			this->checkBoxSocketPuerto->Location = System::Drawing::Point(199, 156);
			this->checkBoxSocketPuerto->Name = L"checkBoxSocketPuerto";
			this->checkBoxSocketPuerto->Size = System::Drawing::Size(15, 14);
			this->checkBoxSocketPuerto->TabIndex = 9;
			this->checkBoxSocketPuerto->UseVisualStyleBackColor = false;
			this->checkBoxSocketPuerto->Click += gcnew System::EventHandler(this, &MyForm::checkBoxSocketPuerto_Click);
			// 
			// checkBoxSocketIP
			// 
			this->checkBoxSocketIP->AutoSize = true;
			this->checkBoxSocketIP->BackColor = System::Drawing::Color::Green;
			this->checkBoxSocketIP->Checked = true;
			this->checkBoxSocketIP->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxSocketIP->Cursor = System::Windows::Forms::Cursors::No;
			this->checkBoxSocketIP->Location = System::Drawing::Point(199, 101);
			this->checkBoxSocketIP->Name = L"checkBoxSocketIP";
			this->checkBoxSocketIP->Size = System::Drawing::Size(15, 14);
			this->checkBoxSocketIP->TabIndex = 8;
			this->checkBoxSocketIP->UseVisualStyleBackColor = false;
			this->checkBoxSocketIP->Click += gcnew System::EventHandler(this, &MyForm::checkBoxSocketIP_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::White;
			this->label7->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->label7->Location = System::Drawing::Point(123, 76);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(17, 13);
			this->label7->TabIndex = 6;
			this->label7->Text = L"IP";
			// 
			// buttonSocketIniciar
			// 
			this->buttonSocketIniciar->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonSocketIniciar->Location = System::Drawing::Point(84, 181);
			this->buttonSocketIniciar->Name = L"buttonSocketIniciar";
			this->buttonSocketIniciar->Size = System::Drawing::Size(95, 23);
			this->buttonSocketIniciar->TabIndex = 4;
			this->buttonSocketIniciar->Text = L"Iniciar";
			this->buttonSocketIniciar->UseVisualStyleBackColor = true;
			this->buttonSocketIniciar->Click += gcnew System::EventHandler(this, &MyForm::ButtonIniciarConnection_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::White;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(111, 128);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(38, 13);
			this->label6->TabIndex = 3;
			this->label6->Text = L"Puerto";
			// 
			// labelSocketServer
			// 
			this->labelSocketServer->AutoSize = true;
			this->labelSocketServer->BackColor = System::Drawing::Color::White;
			this->labelSocketServer->Font = (gcnew System::Drawing::Font(L"MS Reference Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->labelSocketServer->Location = System::Drawing::Point(64, 23);
			this->labelSocketServer->Name = L"labelSocketServer";
			this->labelSocketServer->Size = System::Drawing::Size(150, 26);
			this->labelSocketServer->TabIndex = 2;
			this->labelSocketServer->Text = L"Puente WEB";
			// 
			// textBoxSocketPuerto
			// 
			this->textBoxSocketPuerto->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBoxSocketPuerto->Location = System::Drawing::Point(84, 149);
			this->textBoxSocketPuerto->Name = L"textBoxSocketPuerto";
			this->textBoxSocketPuerto->Size = System::Drawing::Size(95, 21);
			this->textBoxSocketPuerto->TabIndex = 0;
			this->textBoxSocketPuerto->Text = L"55555";
			this->textBoxSocketPuerto->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBoxSocketPuerto->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxSocketIniciarConnection_TextChanged);
			// 
			// shapeContainer3
			// 
			this->shapeContainer3->Location = System::Drawing::Point(3, 3);
			this->shapeContainer3->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer3->Name = L"shapeContainer3";
			this->shapeContainer3->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(2) {this->rectangleShape20, 
				this->rectangleShape3});
			this->shapeContainer3->Size = System::Drawing::Size(272, 228);
			this->shapeContainer3->TabIndex = 10;
			this->shapeContainer3->TabStop = false;
			// 
			// rectangleShape20
			// 
			this->rectangleShape20->BackColor = System::Drawing::Color::White;
			this->rectangleShape20->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape20->Location = System::Drawing::Point(49, 60);
			this->rectangleShape20->Name = L"rectangleShape20";
			this->rectangleShape20->Size = System::Drawing::Size(169, 155);
			// 
			// rectangleShape3
			// 
			this->rectangleShape3->BackColor = System::Drawing::Color::White;
			this->rectangleShape3->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape3->BorderStyle = System::Drawing::Drawing2D::DashStyle::Dash;
			this->rectangleShape3->Location = System::Drawing::Point(47, 16);
			this->rectangleShape3->Name = L"rectangleShape3";
			this->rectangleShape3->Size = System::Drawing::Size(172, 37);
			// 
			// tabPageWeb
			// 
			this->tabPageWeb->BackColor = System::Drawing::Color::Turquoise;
			this->tabPageWeb->Controls->Add(this->buttonConnectarHost);
			this->tabPageWeb->Controls->Add(this->buttonDescanectarServerWeb);
			this->tabPageWeb->Controls->Add(this->labelMostrarHost);
			this->tabPageWeb->Controls->Add(this->label1ServerWeb);
			this->tabPageWeb->Controls->Add(this->labelHost);
			this->tabPageWeb->Controls->Add(this->comboBoxHost);
			this->tabPageWeb->Controls->Add(this->textBoxHostPuerto);
			this->tabPageWeb->Controls->Add(this->labelPuertoWeb);
			this->tabPageWeb->Controls->Add(this->shapeContainer8);
			this->tabPageWeb->Location = System::Drawing::Point(4, 22);
			this->tabPageWeb->Name = L"tabPageWeb";
			this->tabPageWeb->Size = System::Drawing::Size(282, 238);
			this->tabPageWeb->TabIndex = 4;
			this->tabPageWeb->Text = L"Web";
			// 
			// buttonConnectarHost
			// 
			this->buttonConnectarHost->BackColor = System::Drawing::Color::White;
			this->buttonConnectarHost->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->buttonConnectarHost->Location = System::Drawing::Point(85, 196);
			this->buttonConnectarHost->Name = L"buttonConnectarHost";
			this->buttonConnectarHost->Size = System::Drawing::Size(100, 23);
			this->buttonConnectarHost->TabIndex = 6;
			this->buttonConnectarHost->Text = L"Conectar";
			this->buttonConnectarHost->UseVisualStyleBackColor = false;
			this->buttonConnectarHost->Click += gcnew System::EventHandler(this, &MyForm::MybuttonConnectarHost_Click);
			// 
			// buttonDescanectarServerWeb
			// 
			this->buttonDescanectarServerWeb->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 9.75F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->buttonDescanectarServerWeb->Location = System::Drawing::Point(70, 212);
			this->buttonDescanectarServerWeb->Name = L"buttonDescanectarServerWeb";
			this->buttonDescanectarServerWeb->Size = System::Drawing::Size(127, 23);
			this->buttonDescanectarServerWeb->TabIndex = 7;
			this->buttonDescanectarServerWeb->Text = L"Desonectar";
			this->buttonDescanectarServerWeb->UseVisualStyleBackColor = true;
			this->buttonDescanectarServerWeb->Visible = false;
			this->buttonDescanectarServerWeb->Click += gcnew System::EventHandler(this, &MyForm::MYbuttonDescanectarServerWeb_Click);
			// 
			// labelMostrarHost
			// 
			this->labelMostrarHost->BackColor = System::Drawing::Color::Turquoise;
			this->labelMostrarHost->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->labelMostrarHost->Location = System::Drawing::Point(12, 46);
			this->labelMostrarHost->Name = L"labelMostrarHost";
			this->labelMostrarHost->Size = System::Drawing::Size(29, 31);
			this->labelMostrarHost->TabIndex = 8;
			this->labelMostrarHost->Text = L"localhost";
			this->labelMostrarHost->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->labelMostrarHost->Visible = false;
			// 
			// label1ServerWeb
			// 
			this->label1ServerWeb->AutoSize = true;
			this->label1ServerWeb->BackColor = System::Drawing::Color::White;
			this->label1ServerWeb->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1ServerWeb->Location = System::Drawing::Point(56, 22);
			this->label1ServerWeb->Name = L"label1ServerWeb";
			this->label1ServerWeb->Size = System::Drawing::Size(153, 29);
			this->label1ServerWeb->TabIndex = 2;
			this->label1ServerWeb->Text = L"Server Web";
			// 
			// labelHost
			// 
			this->labelHost->BackColor = System::Drawing::Color::White;
			this->labelHost->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->labelHost->Location = System::Drawing::Point(67, 73);
			this->labelHost->Name = L"labelHost";
			this->labelHost->Size = System::Drawing::Size(142, 18);
			this->labelHost->TabIndex = 4;
			this->labelHost->Text = L"Host";
			this->labelHost->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// comboBoxHost
			// 
			this->comboBoxHost->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->comboBoxHost->FormattingEnabled = true;
			this->comboBoxHost->Location = System::Drawing::Point(70, 97);
			this->comboBoxHost->Name = L"comboBoxHost";
			this->comboBoxHost->Size = System::Drawing::Size(127, 24);
			this->comboBoxHost->TabIndex = 0;
			this->comboBoxHost->Text = L"localhost";
			// 
			// textBoxHostPuerto
			// 
			this->textBoxHostPuerto->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBoxHostPuerto->Location = System::Drawing::Point(70, 158);
			this->textBoxHostPuerto->Name = L"textBoxHostPuerto";
			this->textBoxHostPuerto->Size = System::Drawing::Size(127, 23);
			this->textBoxHostPuerto->TabIndex = 1;
			this->textBoxHostPuerto->Text = L"8080";
			this->textBoxHostPuerto->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// labelPuertoWeb
			// 
			this->labelPuertoWeb->BackColor = System::Drawing::Color::White;
			this->labelPuertoWeb->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->labelPuertoWeb->Location = System::Drawing::Point(67, 134);
			this->labelPuertoWeb->Name = L"labelPuertoWeb";
			this->labelPuertoWeb->Size = System::Drawing::Size(142, 16);
			this->labelPuertoWeb->TabIndex = 5;
			this->labelPuertoWeb->Text = L"Puerto";
			this->labelPuertoWeb->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// shapeContainer8
			// 
			this->shapeContainer8->Location = System::Drawing::Point(0, 0);
			this->shapeContainer8->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer8->Name = L"shapeContainer8";
			this->shapeContainer8->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(2) {this->rectangleShape27, 
				this->rectangleShape25});
			this->shapeContainer8->Size = System::Drawing::Size(282, 238);
			this->shapeContainer8->TabIndex = 9;
			this->shapeContainer8->TabStop = false;
			// 
			// rectangleShape27
			// 
			this->rectangleShape27->BackColor = System::Drawing::Color::White;
			this->rectangleShape27->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape27->Location = System::Drawing::Point(53, 18);
			this->rectangleShape27->Name = L"rectangleShape27";
			this->rectangleShape27->Size = System::Drawing::Size(160, 39);
			// 
			// rectangleShape25
			// 
			this->rectangleShape25->BackColor = System::Drawing::Color::White;
			this->rectangleShape25->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape25->Location = System::Drawing::Point(48, 66);
			this->rectangleShape25->Name = L"rectangleShape25";
			this->rectangleShape25->Size = System::Drawing::Size(170, 160);
			// 
			// timer1
			// 
			this->timer1->Interval = 500;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// tabControl3
			// 
			this->tabControl3->Controls->Add(this->tabPage2);
			this->tabControl3->Location = System::Drawing::Point(588, 30);
			this->tabControl3->Name = L"tabControl3";
			this->tabControl3->SelectedIndex = 0;
			this->tabControl3->Size = System::Drawing::Size(282, 264);
			this->tabControl3->TabIndex = 11;
			this->tabControl3->Visible = false;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->labelSocketPuenteTabControl3);
			this->tabPage2->Controls->Add(this->labelCOMPuenteTabControl3);
			this->tabPage2->Controls->Add(this->buttonDesconectarPuente);
			this->tabPage2->Controls->Add(this->label4);
			this->tabPage2->Controls->Add(this->shapeContainer4);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(274, 238);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"COM-Socket";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// labelSocketPuenteTabControl3
			// 
			this->labelSocketPuenteTabControl3->BackColor = System::Drawing::Color::Chartreuse;
			this->labelSocketPuenteTabControl3->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 14.25F, System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->labelSocketPuenteTabControl3->Location = System::Drawing::Point(6, 170);
			this->labelSocketPuenteTabControl3->Name = L"labelSocketPuenteTabControl3";
			this->labelSocketPuenteTabControl3->Size = System::Drawing::Size(262, 28);
			this->labelSocketPuenteTabControl3->TabIndex = 3;
			this->labelSocketPuenteTabControl3->Text = L"127.0.0.1:5555";
			this->labelSocketPuenteTabControl3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->labelSocketPuenteTabControl3->DoubleClick += gcnew System::EventHandler(this, &MyForm::labelSocketPuenteTabControl3_DoubleClick);
			// 
			// labelCOMPuenteTabControl3
			// 
			this->labelCOMPuenteTabControl3->BackColor = System::Drawing::Color::Chartreuse;
			this->labelCOMPuenteTabControl3->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 14.25F, System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->labelCOMPuenteTabControl3->Location = System::Drawing::Point(6, 63);
			this->labelCOMPuenteTabControl3->Name = L"labelCOMPuenteTabControl3";
			this->labelCOMPuenteTabControl3->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->labelCOMPuenteTabControl3->Size = System::Drawing::Size(262, 28);
			this->labelCOMPuenteTabControl3->TabIndex = 2;
			this->labelCOMPuenteTabControl3->Text = L"COM2:115200";
			this->labelCOMPuenteTabControl3->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// buttonDesconectarPuente
			// 
			this->buttonDesconectarPuente->BackColor = System::Drawing::Color::Transparent;
			this->buttonDesconectarPuente->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonDesconectarPuente->Location = System::Drawing::Point(187, 204);
			this->buttonDesconectarPuente->Name = L"buttonDesconectarPuente";
			this->buttonDesconectarPuente->Size = System::Drawing::Size(84, 23);
			this->buttonDesconectarPuente->TabIndex = 1;
			this->buttonDesconectarPuente->Text = L"Desconectar";
			this->buttonDesconectarPuente->UseVisualStyleBackColor = false;
			this->buttonDesconectarPuente->Click += gcnew System::EventHandler(this, &MyForm::buttonDesconectarPuente_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(81, 10);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(111, 32);
			this->label4->TabIndex = 0;
			this->label4->Text = L"Puente";
			// 
			// shapeContainer4
			// 
			this->shapeContainer4->Location = System::Drawing::Point(3, 3);
			this->shapeContainer4->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer4->Name = L"shapeContainer4";
			this->shapeContainer4->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(18) {this->rectangleShape28, 
				this->rectangleShape24, this->rectangleShape23, this->rectangleShape19, this->rectangleShape18, this->rectangleShape17, this->rectangleShape16, 
				this->rectangleShape15, this->rectangleShape14, this->rectangleShape13, this->rectangleShape12, this->rectangleShape11, this->rectangleShape10, 
				this->rectangleShape9, this->rectangleShape8, this->rectangleShape7, this->rectangleShape6, this->rectangleShape4});
			this->shapeContainer4->Size = System::Drawing::Size(268, 232);
			this->shapeContainer4->TabIndex = 4;
			this->shapeContainer4->TabStop = false;
			// 
			// rectangleShape28
			// 
			this->rectangleShape28->BackColor = System::Drawing::Color::Chartreuse;
			this->rectangleShape28->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape28->Location = System::Drawing::Point(145, 60);
			this->rectangleShape28->Name = L"rectangleShape28";
			this->rectangleShape28->Size = System::Drawing::Size(133, 134);
			// 
			// rectangleShape24
			// 
			this->rectangleShape24->BackColor = System::Drawing::Color::Chartreuse;
			this->rectangleShape24->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape24->Location = System::Drawing::Point(1, 60);
			this->rectangleShape24->Name = L"rectangleShape24";
			this->rectangleShape24->Size = System::Drawing::Size(133, 134);
			// 
			// rectangleShape23
			// 
			this->rectangleShape23->Location = System::Drawing::Point(62, 2);
			this->rectangleShape23->Name = L"rectangleShape23";
			this->rectangleShape23->Size = System::Drawing::Size(141, 45);
			// 
			// rectangleShape19
			// 
			this->rectangleShape19->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape19->Location = System::Drawing::Point(137, 160);
			this->rectangleShape19->Name = L"rectangleShape19";
			this->rectangleShape19->Size = System::Drawing::Size(5, 5);
			// 
			// rectangleShape18
			// 
			this->rectangleShape18->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape18->Location = System::Drawing::Point(137, 155);
			this->rectangleShape18->Name = L"rectangleShape18";
			this->rectangleShape18->Size = System::Drawing::Size(5, 5);
			// 
			// rectangleShape17
			// 
			this->rectangleShape17->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape17->Location = System::Drawing::Point(137, 150);
			this->rectangleShape17->Name = L"rectangleShape17";
			this->rectangleShape17->Size = System::Drawing::Size(5, 5);
			// 
			// rectangleShape16
			// 
			this->rectangleShape16->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape16->Location = System::Drawing::Point(137, 145);
			this->rectangleShape16->Name = L"rectangleShape16";
			this->rectangleShape16->Size = System::Drawing::Size(5, 5);
			// 
			// rectangleShape15
			// 
			this->rectangleShape15->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape15->Location = System::Drawing::Point(137, 140);
			this->rectangleShape15->Name = L"rectangleShape15";
			this->rectangleShape15->Size = System::Drawing::Size(5, 5);
			// 
			// rectangleShape14
			// 
			this->rectangleShape14->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape14->Location = System::Drawing::Point(137, 135);
			this->rectangleShape14->Name = L"rectangleShape14";
			this->rectangleShape14->Size = System::Drawing::Size(5, 5);
			// 
			// rectangleShape13
			// 
			this->rectangleShape13->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape13->Location = System::Drawing::Point(137, 130);
			this->rectangleShape13->Name = L"rectangleShape13";
			this->rectangleShape13->Size = System::Drawing::Size(5, 5);
			// 
			// rectangleShape12
			// 
			this->rectangleShape12->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape12->Location = System::Drawing::Point(137, 125);
			this->rectangleShape12->Name = L"rectangleShape12";
			this->rectangleShape12->Size = System::Drawing::Size(5, 5);
			// 
			// rectangleShape11
			// 
			this->rectangleShape11->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape11->Location = System::Drawing::Point(137, 120);
			this->rectangleShape11->Name = L"rectangleShape11";
			this->rectangleShape11->Size = System::Drawing::Size(5, 5);
			// 
			// rectangleShape10
			// 
			this->rectangleShape10->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape10->Location = System::Drawing::Point(137, 115);
			this->rectangleShape10->Name = L"rectangleShape10";
			this->rectangleShape10->Size = System::Drawing::Size(5, 5);
			// 
			// rectangleShape9
			// 
			this->rectangleShape9->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape9->Location = System::Drawing::Point(137, 110);
			this->rectangleShape9->Name = L"rectangleShape9";
			this->rectangleShape9->Size = System::Drawing::Size(5, 5);
			// 
			// rectangleShape8
			// 
			this->rectangleShape8->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape8->Location = System::Drawing::Point(137, 105);
			this->rectangleShape8->Name = L"rectangleShape8";
			this->rectangleShape8->Size = System::Drawing::Size(5, 5);
			// 
			// rectangleShape7
			// 
			this->rectangleShape7->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape7->Location = System::Drawing::Point(137, 100);
			this->rectangleShape7->Name = L"rectangleShape7";
			this->rectangleShape7->Size = System::Drawing::Size(5, 5);
			// 
			// rectangleShape6
			// 
			this->rectangleShape6->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape6->Location = System::Drawing::Point(137, 95);
			this->rectangleShape6->Name = L"rectangleShape6";
			this->rectangleShape6->Size = System::Drawing::Size(5, 5);
			// 
			// rectangleShape4
			// 
			this->rectangleShape4->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape4->Location = System::Drawing::Point(137, 90);
			this->rectangleShape4->Name = L"rectangleShape4";
			this->rectangleShape4->Size = System::Drawing::Size(5, 5);
			// 
			// timer2
			// 
			this->timer2->Interval = 500;
			this->timer2->Tick += gcnew System::EventHandler(this, &MyForm::timer2_Tick);
			// 
			// tabPageSocketClientesTabControl2
			// 
			this->tabPageSocketClientesTabControl2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->tabPageSocketClientesTabControl2->Controls->Add(this->buttonNOAcceso);
			this->tabPageSocketClientesTabControl2->Controls->Add(this->flowLayoutPanel1);
			this->tabPageSocketClientesTabControl2->Controls->Add(this->buttonDesconectar);
			this->tabPageSocketClientesTabControl2->Controls->Add(this->button30);
			this->tabPageSocketClientesTabControl2->Controls->Add(this->buttonAcceso);
			this->tabPageSocketClientesTabControl2->Controls->Add(this->button29);
			this->tabPageSocketClientesTabControl2->Controls->Add(this->button28);
			this->tabPageSocketClientesTabControl2->Controls->Add(this->button27);
			this->tabPageSocketClientesTabControl2->Controls->Add(this->button26);
			this->tabPageSocketClientesTabControl2->Controls->Add(this->button25);
			this->tabPageSocketClientesTabControl2->Controls->Add(this->button24);
			this->tabPageSocketClientesTabControl2->Controls->Add(this->button23);
			this->tabPageSocketClientesTabControl2->Controls->Add(this->button22);
			this->tabPageSocketClientesTabControl2->Controls->Add(this->button21);
			this->tabPageSocketClientesTabControl2->Controls->Add(this->label9);
			this->tabPageSocketClientesTabControl2->Controls->Add(this->label8);
			this->tabPageSocketClientesTabControl2->Controls->Add(this->shapeContainer7);
			this->tabPageSocketClientesTabControl2->Location = System::Drawing::Point(4, 22);
			this->tabPageSocketClientesTabControl2->Name = L"tabPageSocketClientesTabControl2";
			this->tabPageSocketClientesTabControl2->Padding = System::Windows::Forms::Padding(3);
			this->tabPageSocketClientesTabControl2->Size = System::Drawing::Size(274, 238);
			this->tabPageSocketClientesTabControl2->TabIndex = 1;
			this->tabPageSocketClientesTabControl2->Text = L"Clientes ";
			this->tabPageSocketClientesTabControl2->UseVisualStyleBackColor = true;
			// 
			// buttonNOAcceso
			// 
			this->buttonNOAcceso->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonNOAcceso->Enabled = false;
			this->buttonNOAcceso->Location = System::Drawing::Point(197, 183);
			this->buttonNOAcceso->Name = L"buttonNOAcceso";
			this->buttonNOAcceso->Size = System::Drawing::Size(67, 23);
			this->buttonNOAcceso->TabIndex = 14;
			this->buttonNOAcceso->Text = L"NoAcceso";
			this->buttonNOAcceso->UseVisualStyleBackColor = true;
			this->buttonNOAcceso->Click += gcnew System::EventHandler(this, &MyForm::buttonNOAcceso_Click);
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->flowLayoutPanel1->Controls->Add(this->labelSocketClientesTabControl2);
			this->flowLayoutPanel1->Location = System::Drawing::Point(134, 3);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->flowLayoutPanel1->Size = System::Drawing::Size(140, 159);
			this->flowLayoutPanel1->TabIndex = 12;
			// 
			// labelSocketClientesTabControl2
			// 
			this->labelSocketClientesTabControl2->AutoSize = true;
			this->labelSocketClientesTabControl2->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 9.75F, System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->labelSocketClientesTabControl2->Location = System::Drawing::Point(3, 0);
			this->labelSocketClientesTabControl2->Name = L"labelSocketClientesTabControl2";
			this->labelSocketClientesTabControl2->Size = System::Drawing::Size(128, 112);
			this->labelSocketClientesTabControl2->TabIndex = 0;
			this->labelSocketClientesTabControl2->Text = L"_Id:0000\r\n_Tipo:NULL\r\n_ACCESO:FALSE\r\n_IP:192.168.191.145\r\n_Date: MON JUL 00 00:00" 
				L" 0000\r\n";
			this->labelSocketClientesTabControl2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->labelSocketClientesTabControl2->Visible = false;
			// 
			// buttonDesconectar
			// 
			this->buttonDesconectar->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonDesconectar->Enabled = false;
			this->buttonDesconectar->Location = System::Drawing::Point(135, 210);
			this->buttonDesconectar->Name = L"buttonDesconectar";
			this->buttonDesconectar->Size = System::Drawing::Size(129, 23);
			this->buttonDesconectar->TabIndex = 1;
			this->buttonDesconectar->Text = L"Desconectar";
			this->buttonDesconectar->UseVisualStyleBackColor = true;
			this->buttonDesconectar->Click += gcnew System::EventHandler(this, &MyForm::buttonDesconectar_Click);
			// 
			// button30
			// 
			this->button30->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button30->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button30->Location = System::Drawing::Point(70, 212);
			this->button30->Name = L"button30";
			this->button30->Size = System::Drawing::Size(58, 21);
			this->button30->TabIndex = 11;
			this->button30->Text = L"Client10";
			this->button30->UseVisualStyleBackColor = true;
			this->button30->Visible = false;
			this->button30->Click += gcnew System::EventHandler(this, &MyForm::button30_Click);
			// 
			// buttonAcceso
			// 
			this->buttonAcceso->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonAcceso->Enabled = false;
			this->buttonAcceso->Location = System::Drawing::Point(135, 183);
			this->buttonAcceso->Name = L"buttonAcceso";
			this->buttonAcceso->Size = System::Drawing::Size(60, 23);
			this->buttonAcceso->TabIndex = 2;
			this->buttonAcceso->Text = L"Acceso";
			this->buttonAcceso->UseVisualStyleBackColor = true;
			this->buttonAcceso->Click += gcnew System::EventHandler(this, &MyForm::buttonAcceso_Click);
			// 
			// button29
			// 
			this->button29->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button29->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button29->Location = System::Drawing::Point(70, 185);
			this->button29->Name = L"button29";
			this->button29->Size = System::Drawing::Size(58, 21);
			this->button29->TabIndex = 10;
			this->button29->Text = L"Cliente 9";
			this->button29->UseVisualStyleBackColor = true;
			this->button29->Visible = false;
			this->button29->Click += gcnew System::EventHandler(this, &MyForm::button29_Click);
			// 
			// button28
			// 
			this->button28->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button28->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button28->Location = System::Drawing::Point(70, 160);
			this->button28->Name = L"button28";
			this->button28->Size = System::Drawing::Size(58, 21);
			this->button28->TabIndex = 9;
			this->button28->Text = L"Cliente 8";
			this->button28->UseVisualStyleBackColor = true;
			this->button28->Visible = false;
			this->button28->Click += gcnew System::EventHandler(this, &MyForm::button28_Click);
			// 
			// button27
			// 
			this->button27->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button27->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button27->Location = System::Drawing::Point(70, 133);
			this->button27->Name = L"button27";
			this->button27->Size = System::Drawing::Size(58, 21);
			this->button27->TabIndex = 8;
			this->button27->Text = L"Cliente 7";
			this->button27->UseVisualStyleBackColor = true;
			this->button27->Visible = false;
			this->button27->Click += gcnew System::EventHandler(this, &MyForm::button27_Click);
			// 
			// button26
			// 
			this->button26->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button26->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button26->Location = System::Drawing::Point(70, 108);
			this->button26->Name = L"button26";
			this->button26->Size = System::Drawing::Size(58, 21);
			this->button26->TabIndex = 7;
			this->button26->Text = L"Cliente 6";
			this->button26->UseVisualStyleBackColor = true;
			this->button26->Visible = false;
			this->button26->Click += gcnew System::EventHandler(this, &MyForm::button26_Click);
			// 
			// button25
			// 
			this->button25->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button25->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button25->Location = System::Drawing::Point(6, 212);
			this->button25->Name = L"button25";
			this->button25->Size = System::Drawing::Size(58, 21);
			this->button25->TabIndex = 6;
			this->button25->Text = L"Cliente 5";
			this->button25->UseVisualStyleBackColor = true;
			this->button25->Visible = false;
			this->button25->Click += gcnew System::EventHandler(this, &MyForm::button25_Click);
			// 
			// button24
			// 
			this->button24->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button24->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button24->Location = System::Drawing::Point(6, 185);
			this->button24->Name = L"button24";
			this->button24->Size = System::Drawing::Size(58, 21);
			this->button24->TabIndex = 5;
			this->button24->Text = L"Cliente 4";
			this->button24->UseVisualStyleBackColor = true;
			this->button24->Visible = false;
			this->button24->Click += gcnew System::EventHandler(this, &MyForm::button24_Click);
			// 
			// button23
			// 
			this->button23->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button23->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button23->Location = System::Drawing::Point(6, 160);
			this->button23->Name = L"button23";
			this->button23->Size = System::Drawing::Size(58, 21);
			this->button23->TabIndex = 4;
			this->button23->Text = L"Cliente 3";
			this->button23->UseVisualStyleBackColor = true;
			this->button23->Visible = false;
			this->button23->Click += gcnew System::EventHandler(this, &MyForm::button23_Click);
			// 
			// button22
			// 
			this->button22->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button22->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button22->Location = System::Drawing::Point(6, 133);
			this->button22->Name = L"button22";
			this->button22->Size = System::Drawing::Size(58, 21);
			this->button22->TabIndex = 3;
			this->button22->Text = L"Cliente 2";
			this->button22->UseVisualStyleBackColor = true;
			this->button22->Visible = false;
			this->button22->Click += gcnew System::EventHandler(this, &MyForm::button22_Click);
			// 
			// button21
			// 
			this->button21->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button21->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button21->Location = System::Drawing::Point(6, 108);
			this->button21->Name = L"button21";
			this->button21->Size = System::Drawing::Size(58, 21);
			this->button21->TabIndex = 2;
			this->button21->Text = L"Cliente 1";
			this->button21->UseVisualStyleBackColor = true;
			this->button21->Visible = false;
			this->button21->Click += gcnew System::EventHandler(this, &MyForm::button21_Click);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Swis721 Blk BT", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(54, 57);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(26, 25);
			this->label9->TabIndex = 1;
			this->label9->Text = L"0";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"MS Reference Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(10, 19);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(105, 26);
			this->label8->TabIndex = 0;
			this->label8->Text = L"Clientes";
			// 
			// shapeContainer7
			// 
			this->shapeContainer7->Location = System::Drawing::Point(3, 3);
			this->shapeContainer7->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer7->Name = L"shapeContainer7";
			this->shapeContainer7->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(3) {this->rectangleShape31, 
				this->rectangleShape30, this->rectangleShapeClientes});
			this->shapeContainer7->Size = System::Drawing::Size(264, 228);
			this->shapeContainer7->TabIndex = 13;
			this->shapeContainer7->TabStop = false;
			// 
			// rectangleShape31
			// 
			this->rectangleShape31->BackColor = System::Drawing::Color::Lime;
			this->rectangleShape31->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape31->Location = System::Drawing::Point(195, 163);
			this->rectangleShape31->Name = L"rectangleShape31";
			this->rectangleShape31->Size = System::Drawing::Size(63, 12);
			this->rectangleShape31->Visible = false;
			// 
			// rectangleShape30
			// 
			this->rectangleShape30->BackColor = System::Drawing::Color::Purple;
			this->rectangleShape30->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape30->Location = System::Drawing::Point(134, 163);
			this->rectangleShape30->Name = L"rectangleShape30";
			this->rectangleShape30->Size = System::Drawing::Size(57, 12);
			this->rectangleShape30->Visible = false;
			// 
			// rectangleShapeClientes
			// 
			this->rectangleShapeClientes->Location = System::Drawing::Point(4, 6);
			this->rectangleShapeClientes->Name = L"rectangleShapeClientes";
			this->rectangleShapeClientes->Size = System::Drawing::Size(118, 81);
			// 
			// tabPageSocketServerTabControl2
			// 
			this->tabPageSocketServerTabControl2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->tabPageSocketServerTabControl2->Controls->Add(this->labelSocketAddrTabControl2);
			this->tabPageSocketServerTabControl2->Controls->Add(this->textBoxSocketDrawTabControl2);
			this->tabPageSocketServerTabControl2->Controls->Add(this->buttonSocketAceptFocusTabControl2);
			this->tabPageSocketServerTabControl2->Controls->Add(this->buttonSocketFocusTabControl2);
			this->tabPageSocketServerTabControl2->Controls->Add(this->checkBoxSocketIPTabControl2);
			this->tabPageSocketServerTabControl2->Controls->Add(this->checkBoxSocketPuertoTabControl2);
			this->tabPageSocketServerTabControl2->Controls->Add(this->labelSocketCOMServerTabControl2);
			this->tabPageSocketServerTabControl2->Controls->Add(this->buttonSocketDisconectTabControl2);
			this->tabPageSocketServerTabControl2->Controls->Add(this->textBoxSocketLowByteTabControl2);
			this->tabPageSocketServerTabControl2->Controls->Add(this->buttonSocketCancelButtonTabControl2);
			this->tabPageSocketServerTabControl2->Controls->Add(this->textBoxSocketHightByteTabControl2);
			this->tabPageSocketServerTabControl2->Controls->Add(this->buttonSocketAceptButtonTabControl2);
			this->tabPageSocketServerTabControl2->Controls->Add(this->buttonSocketEnviarTabControl2);
			this->tabPageSocketServerTabControl2->Controls->Add(this->buttonSocketRedireccionarTabControl2);
			this->tabPageSocketServerTabControl2->Controls->Add(this->shapeContainer5);
			this->tabPageSocketServerTabControl2->Location = System::Drawing::Point(4, 22);
			this->tabPageSocketServerTabControl2->Name = L"tabPageSocketServerTabControl2";
			this->tabPageSocketServerTabControl2->Padding = System::Windows::Forms::Padding(3);
			this->tabPageSocketServerTabControl2->Size = System::Drawing::Size(274, 238);
			this->tabPageSocketServerTabControl2->TabIndex = 0;
			this->tabPageSocketServerTabControl2->Text = L"Server";
			this->tabPageSocketServerTabControl2->UseVisualStyleBackColor = true;
			// 
			// labelSocketAddrTabControl2
			// 
			this->labelSocketAddrTabControl2->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 12, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->labelSocketAddrTabControl2->Location = System::Drawing::Point(3, 51);
			this->labelSocketAddrTabControl2->Name = L"labelSocketAddrTabControl2";
			this->labelSocketAddrTabControl2->Size = System::Drawing::Size(271, 19);
			this->labelSocketAddrTabControl2->TabIndex = 17;
			this->labelSocketAddrTabControl2->Text = L"127.0.0.1:5555";
			this->labelSocketAddrTabControl2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->labelSocketAddrTabControl2->DoubleClick += gcnew System::EventHandler(this, &MyForm::labelSocketAddrTabControl2_DoubleClick);
			// 
			// textBoxSocketDrawTabControl2
			// 
			this->textBoxSocketDrawTabControl2->AutoSize = true;
			this->textBoxSocketDrawTabControl2->Location = System::Drawing::Point(46, 158);
			this->textBoxSocketDrawTabControl2->Name = L"textBoxSocketDrawTabControl2";
			this->textBoxSocketDrawTabControl2->Size = System::Drawing::Size(53, 17);
			this->textBoxSocketDrawTabControl2->TabIndex = 16;
			this->textBoxSocketDrawTabControl2->Text = L"Pintar";
			this->textBoxSocketDrawTabControl2->UseVisualStyleBackColor = true;
			this->textBoxSocketDrawTabControl2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxSocketDrawTabControl2_Click);
			// 
			// buttonSocketAceptFocusTabControl2
			// 
			this->buttonSocketAceptFocusTabControl2->Location = System::Drawing::Point(209, 95);
			this->buttonSocketAceptFocusTabControl2->Name = L"buttonSocketAceptFocusTabControl2";
			this->buttonSocketAceptFocusTabControl2->Size = System::Drawing::Size(25, 23);
			this->buttonSocketAceptFocusTabControl2->TabIndex = 15;
			this->buttonSocketAceptFocusTabControl2->Text = L"A";
			this->buttonSocketAceptFocusTabControl2->UseVisualStyleBackColor = true;
			this->buttonSocketAceptFocusTabControl2->Click += gcnew System::EventHandler(this, &MyForm::buttonSocketAceptFocusTabControl2_Click);
			// 
			// buttonSocketFocusTabControl2
			// 
			this->buttonSocketFocusTabControl2->Location = System::Drawing::Point(178, 95);
			this->buttonSocketFocusTabControl2->Name = L"buttonSocketFocusTabControl2";
			this->buttonSocketFocusTabControl2->Size = System::Drawing::Size(25, 24);
			this->buttonSocketFocusTabControl2->TabIndex = 14;
			this->buttonSocketFocusTabControl2->Text = L"F";
			this->buttonSocketFocusTabControl2->UseVisualStyleBackColor = true;
			this->buttonSocketFocusTabControl2->Click += gcnew System::EventHandler(this, &MyForm::buttonSocketFocusTabControl2_Click);
			// 
			// checkBoxSocketIPTabControl2
			// 
			this->checkBoxSocketIPTabControl2->AutoSize = true;
			this->checkBoxSocketIPTabControl2->BackColor = System::Drawing::Color::Green;
			this->checkBoxSocketIPTabControl2->Checked = true;
			this->checkBoxSocketIPTabControl2->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxSocketIPTabControl2->Cursor = System::Windows::Forms::Cursors::No;
			this->checkBoxSocketIPTabControl2->Location = System::Drawing::Point(14, 132);
			this->checkBoxSocketIPTabControl2->Name = L"checkBoxSocketIPTabControl2";
			this->checkBoxSocketIPTabControl2->Size = System::Drawing::Size(15, 14);
			this->checkBoxSocketIPTabControl2->TabIndex = 13;
			this->checkBoxSocketIPTabControl2->UseVisualStyleBackColor = false;
			this->checkBoxSocketIPTabControl2->Click += gcnew System::EventHandler(this, &MyForm::checkBoxSocketsPuertoTabControl2_Click);
			// 
			// checkBoxSocketPuertoTabControl2
			// 
			this->checkBoxSocketPuertoTabControl2->AutoSize = true;
			this->checkBoxSocketPuertoTabControl2->BackColor = System::Drawing::Color::Green;
			this->checkBoxSocketPuertoTabControl2->Checked = true;
			this->checkBoxSocketPuertoTabControl2->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxSocketPuertoTabControl2->Cursor = System::Windows::Forms::Cursors::No;
			this->checkBoxSocketPuertoTabControl2->Location = System::Drawing::Point(14, 93);
			this->checkBoxSocketPuertoTabControl2->Name = L"checkBoxSocketPuertoTabControl2";
			this->checkBoxSocketPuertoTabControl2->Size = System::Drawing::Size(15, 14);
			this->checkBoxSocketPuertoTabControl2->TabIndex = 12;
			this->checkBoxSocketPuertoTabControl2->UseVisualStyleBackColor = false;
			this->checkBoxSocketPuertoTabControl2->Click += gcnew System::EventHandler(this, &MyForm::checkBoxSocketsIPTabControl2_Click);
			// 
			// labelSocketCOMServerTabControl2
			// 
			this->labelSocketCOMServerTabControl2->AutoSize = true;
			this->labelSocketCOMServerTabControl2->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 20.25F, System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->labelSocketCOMServerTabControl2->Location = System::Drawing::Point(29, 10);
			this->labelSocketCOMServerTabControl2->Name = L"labelSocketCOMServerTabControl2";
			this->labelSocketCOMServerTabControl2->Size = System::Drawing::Size(223, 32);
			this->labelSocketCOMServerTabControl2->TabIndex = 11;
			this->labelSocketCOMServerTabControl2->Text = L"Socket Server";
			// 
			// buttonSocketDisconectTabControl2
			// 
			this->buttonSocketDisconectTabControl2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonSocketDisconectTabControl2->Location = System::Drawing::Point(191, 209);
			this->buttonSocketDisconectTabControl2->Name = L"buttonSocketDisconectTabControl2";
			this->buttonSocketDisconectTabControl2->Size = System::Drawing::Size(77, 23);
			this->buttonSocketDisconectTabControl2->TabIndex = 10;
			this->buttonSocketDisconectTabControl2->Text = L"Desconectar";
			this->buttonSocketDisconectTabControl2->UseVisualStyleBackColor = true;
			this->buttonSocketDisconectTabControl2->Click += gcnew System::EventHandler(this, &MyForm::buttonSocketDisconectTabControl2_Click);
			// 
			// textBoxSocketLowByteTabControl2
			// 
			this->textBoxSocketLowByteTabControl2->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 12, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->textBoxSocketLowByteTabControl2->Location = System::Drawing::Point(35, 125);
			this->textBoxSocketLowByteTabControl2->MaxLength = 8;
			this->textBoxSocketLowByteTabControl2->Name = L"textBoxSocketLowByteTabControl2";
			this->textBoxSocketLowByteTabControl2->Size = System::Drawing::Size(93, 27);
			this->textBoxSocketLowByteTabControl2->TabIndex = 6;
			this->textBoxSocketLowByteTabControl2->Text = L"00000001";
			this->textBoxSocketLowByteTabControl2->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxSocketBytesTabControl2_TextChanged);
			// 
			// buttonSocketCancelButtonTabControl2
			// 
			this->buttonSocketCancelButtonTabControl2->BackColor = System::Drawing::Color::Red;
			this->buttonSocketCancelButtonTabControl2->Location = System::Drawing::Point(240, 95);
			this->buttonSocketCancelButtonTabControl2->Name = L"buttonSocketCancelButtonTabControl2";
			this->buttonSocketCancelButtonTabControl2->Size = System::Drawing::Size(12, 51);
			this->buttonSocketCancelButtonTabControl2->TabIndex = 9;
			this->buttonSocketCancelButtonTabControl2->UseVisualStyleBackColor = false;
			this->buttonSocketCancelButtonTabControl2->Click += gcnew System::EventHandler(this, &MyForm::buttonSocketCancelButtonTabControl2_Click);
			// 
			// textBoxSocketHightByteTabControl2
			// 
			this->textBoxSocketHightByteTabControl2->Font = (gcnew System::Drawing::Font(L"Monospac821 BT", 12, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->textBoxSocketHightByteTabControl2->Location = System::Drawing::Point(35, 88);
			this->textBoxSocketHightByteTabControl2->MaxLength = 8;
			this->textBoxSocketHightByteTabControl2->Name = L"textBoxSocketHightByteTabControl2";
			this->textBoxSocketHightByteTabControl2->Size = System::Drawing::Size(93, 27);
			this->textBoxSocketHightByteTabControl2->TabIndex = 5;
			this->textBoxSocketHightByteTabControl2->Text = L"00000001";
			this->textBoxSocketHightByteTabControl2->TextChanged += gcnew System::EventHandler(this, &MyForm::textBoxSocketBytesTabControl2_TextChanged);
			// 
			// buttonSocketAceptButtonTabControl2
			// 
			this->buttonSocketAceptButtonTabControl2->BackColor = System::Drawing::Color::Lime;
			this->buttonSocketAceptButtonTabControl2->ForeColor = System::Drawing::SystemColors::ControlText;
			this->buttonSocketAceptButtonTabControl2->Location = System::Drawing::Point(178, 149);
			this->buttonSocketAceptButtonTabControl2->Name = L"buttonSocketAceptButtonTabControl2";
			this->buttonSocketAceptButtonTabControl2->Size = System::Drawing::Size(74, 12);
			this->buttonSocketAceptButtonTabControl2->TabIndex = 8;
			this->buttonSocketAceptButtonTabControl2->UseVisualStyleBackColor = false;
			this->buttonSocketAceptButtonTabControl2->Click += gcnew System::EventHandler(this, &MyForm::buttonSocketAceptButtonTabControl2_Click);
			// 
			// buttonSocketEnviarTabControl2
			// 
			this->buttonSocketEnviarTabControl2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->buttonSocketEnviarTabControl2->Location = System::Drawing::Point(35, 181);
			this->buttonSocketEnviarTabControl2->Name = L"buttonSocketEnviarTabControl2";
			this->buttonSocketEnviarTabControl2->Size = System::Drawing::Size(82, 23);
			this->buttonSocketEnviarTabControl2->TabIndex = 4;
			this->buttonSocketEnviarTabControl2->Text = L"Enviar";
			this->buttonSocketEnviarTabControl2->UseVisualStyleBackColor = true;
			this->buttonSocketEnviarTabControl2->Click += gcnew System::EventHandler(this, &MyForm::buttonSocketEnviarTabControl2_Click);
			// 
			// buttonSocketRedireccionarTabControl2
			// 
			this->buttonSocketRedireccionarTabControl2->Location = System::Drawing::Point(178, 121);
			this->buttonSocketRedireccionarTabControl2->Name = L"buttonSocketRedireccionarTabControl2";
			this->buttonSocketRedireccionarTabControl2->Size = System::Drawing::Size(56, 26);
			this->buttonSocketRedireccionarTabControl2->TabIndex = 7;
			this->buttonSocketRedireccionarTabControl2->Text = L"R";
			this->buttonSocketRedireccionarTabControl2->UseVisualStyleBackColor = true;
			this->buttonSocketRedireccionarTabControl2->Click += gcnew System::EventHandler(this, &MyForm::buttonRedireccionar_Click);
			// 
			// shapeContainer5
			// 
			this->shapeContainer5->Location = System::Drawing::Point(3, 3);
			this->shapeContainer5->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer5->Name = L"shapeContainer5";
			this->shapeContainer5->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(2) {this->rectangleShape22, 
				this->rectangleShape5});
			this->shapeContainer5->Size = System::Drawing::Size(264, 228);
			this->shapeContainer5->TabIndex = 18;
			this->shapeContainer5->TabStop = false;
			// 
			// rectangleShape22
			// 
			this->rectangleShape22->Location = System::Drawing::Point(6, 72);
			this->rectangleShape22->Name = L"rectangleShape22";
			this->rectangleShape22->Size = System::Drawing::Size(133, 141);
			// 
			// rectangleShape5
			// 
			this->rectangleShape5->BackColor = System::Drawing::Color::WhiteSmoke;
			this->rectangleShape5->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape5->Location = System::Drawing::Point(165, 81);
			this->rectangleShape5->Name = L"rectangleShape5";
			this->rectangleShape5->Size = System::Drawing::Size(93, 86);
			// 
			// tabControl2
			// 
			this->tabControl2->Controls->Add(this->tabPageSocketServerTabControl2);
			this->tabControl2->Controls->Add(this->tabPageSocketClientesTabControl2);
			this->tabControl2->Location = System::Drawing::Point(12, 30);
			this->tabControl2->Name = L"tabControl2";
			this->tabControl2->SelectedIndex = 0;
			this->tabControl2->Size = System::Drawing::Size(282, 264);
			this->tabControl2->TabIndex = 10;
			this->tabControl2->Visible = false;
			// 
			// timer3
			// 
			this->timer3->Interval = 500;
			this->timer3->Tick += gcnew System::EventHandler(this, &MyForm::timer3_Tick);
			// 
			// rectangleShape29
			// 
			this->rectangleShape29->BackColor = System::Drawing::Color::White;
			this->rectangleShape29->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape29->Location = System::Drawing::Point(13, 16);
			this->rectangleShape29->Name = L"rectangleShape29";
			this->rectangleShape29->Size = System::Drawing::Size(248, 48);
			// 
			// shapeContainer6
			// 
			this->shapeContainer6->Location = System::Drawing::Point(3, 3);
			this->shapeContainer6->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer6->Name = L"shapeContainer6";
			this->shapeContainer6->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(3) {this->lineShape1, 
				this->rectangleShape32, this->rectangleShape29});
			this->shapeContainer6->Size = System::Drawing::Size(276, 232);
			this->shapeContainer6->TabIndex = 10;
			this->shapeContainer6->TabStop = false;
			// 
			// rectangleShape32
			// 
			this->rectangleShape32->BackColor = System::Drawing::Color::White;
			this->rectangleShape32->BackStyle = Microsoft::VisualBasic::PowerPacks::BackStyle::Opaque;
			this->rectangleShape32->Location = System::Drawing::Point(14, 77);
			this->rectangleShape32->Name = L"rectangleShape32";
			this->rectangleShape32->Size = System::Drawing::Size(63, 83);
			// 
			// lineShape1
			// 
			this->lineShape1->Name = L"lineShape1";
			this->lineShape1->X1 = 20;
			this->lineShape1->X2 = 70;
			this->lineShape1->Y1 = 117;
			this->lineShape1->Y2 = 117;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(884, 343);
			this->Controls->Add(this->tabControl3);
			this->Controls->Add(this->tabControl2);
			this->Controls->Add(this->tabControl1);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(900, 900);
			this->MinimumSize = System::Drawing::Size(300, 300);
			this->Name = L"MyForm";
			this->Text = L"ESE_GRS_Connection_Simulator";
			this->tabControl1->ResumeLayout(false);
			this->tabPageAbout->ResumeLayout(false);
			this->tabPageAbout->PerformLayout();
			this->flowLayoutPanel2->ResumeLayout(false);
			this->tabPageCOM->ResumeLayout(false);
			this->tabPageCOM->PerformLayout();
			this->tabPageSocketCliente->ResumeLayout(false);
			this->tabPageSocketCliente->PerformLayout();
			this->tabPagePuente->ResumeLayout(false);
			this->tabPagePuente->PerformLayout();
			this->tabPageSocket->ResumeLayout(false);
			this->tabPageSocket->PerformLayout();
			this->tabPageWeb->ResumeLayout(false);
			this->tabPageWeb->PerformLayout();
			this->tabControl3->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->tabPageSocketClientesTabControl2->ResumeLayout(false);
			this->tabPageSocketClientesTabControl2->PerformLayout();
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->tabPageSocketServerTabControl2->ResumeLayout(false);
			this->tabPageSocketServerTabControl2->PerformLayout();
			this->tabControl2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
//private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
//			 if(comboBox1->Text!="SERIAL___PORT"&&comboBox1->Text!="TCP_IP_SERVER"&&comboBox1->Text!="TCP_IP_CLIENT")
//			 {
//				 textBoxCOMPuerto->Enabled=false;
//				 textBoxCOMVelocidad->Enabled=false;
//				 buttonCOMIniciar->Enabled=false;
//				 return;
//			 }
//			 textBoxCOMPuerto->Enabled=true;
//			 textBoxCOMVelocidad->Enabled=true;
//			 buttonCOMIniciar->Enabled=true;
//			 if(comboBox1->Text=="SERIAL___PORT")
//			 {
//				 c[0]->SetType(ConnectionType::SERIAL_PORT,c);
//				 textBoxCOMPuerto->Text="COM1";
//				 textBoxCOMVelocidad->Text="9600";
//			 }
//			 else if(comboBox1->Text=="TCP_IP_SERVER")
//			 {
//				 c[0]->SetType(ConnectionType::TCP_IP_SERVER,c);
//				 textBoxCOMPuerto->Text="127.0.0.1";
//				 textBoxCOMVelocidad->Text="55555";
//			 }
//			 else if(comboBox1->Text=="TCP_IP_CLIENT")
//			 {
//				 c[0]->SetType(ConnectionType::TCP_IP_CLIENT,c);
//				 textBoxCOMPuerto->Text="127.0.0.1";
//				 textBoxCOMVelocidad->Text="55555";
//			 }
//
//		 }
//private: System::Void OnTExtChanged(System::Object^  sender, System::EventArgs^  e) {
//			if(comboBox1->Text!="SERIAL___PORT"&&comboBox1->Text!="TCP_IP_SERVER"&&comboBox1->Text!="TCP_IP_CLIENT")
//			 {
//				 textBoxCOMPuerto->Enabled=false;
//				 textBoxCOMVelocidad->Enabled=false;
//				 buttonCOMIniciar->Enabled=false;
//				 return;
//			 }
//			
//		 }
//private: System::Void ButtonIniciarConnection_Click(System::Object^  sender, System::EventArgs^  e) {
//			 if(Interfaz==0)
//			 {
//				 Interfaz=1;
//			    const char*txb1=context.marshal_as<const char*>(textBoxCOMPuerto->Text);
//			    const char*txb2=context.marshal_as<const char*>(textBoxCOMVelocidad->Text);
//			    if(c[0]->GetType()==ConnectionType::SERIAL_PORT)
//			       c=new COM();
//		        else if(c[0]->GetType()==ConnectionType::TCP_IP_CLIENT)
//			      c=new TcP_ip_Client();
//		        else if(c[0]->GetType()==ConnectionType::TCP_IP_SERVER)
//			       c=new TcP_ip_Server();
//
//			    if(!c[0]->inicializa(txb1,atol(txb2)))
//			    {
//				    labelError->Text=gcnew String(c[0]->ErrorStr());
//				    System::Windows::Forms::MessageBox::Show(labelError->Text);
//				    labelError->Visible=true;
//					Interfaz=0;
//				    return;
//			    }
//			    Interfaz05();
//			}
//			 else if(Interfaz==1)
//			 {
//				 if(SendCont)
//				 {
//					 InterfazAutoSend(false);
//				 }
//				 Interfaz=0;
//				 Interfaz0();
//				 c[0]->CloseConnection();
//				 
//
//			 }
//			     
//		 }
//public:
//	void Interfaz0()
//	{
//		labelError->Visible=false;
//		labelConnectionType->Visible=false;
//		labelCharUnsignedConnection->Visible=false;
//		radioButtonESE_GRS->Visible=false;
//		radioButtonNormal->Visible=false;
//		buttonRedireccionar->Visible=false;
//		buttonSocketIniciar->Visible=false;
//		checkBoxDraw->Visible=false;
//		checkBoxCode->Visible=false;
//		buttonSend->Visible=false;
//		buttonAcept->Visible=false;
//		buttonCancel->Visible=false;
//		buttonFocusClick->Visible=false;
//		buttonNextFocus->Visible=false;
//		checkBoxAutoVerif->Visible=false;
//		checkBoxAutoSend->Visible=false;
//		buttonAuto->Visible=false;
//		textBoxAutoS->Visible=false;
//		textBoxCOMVelocidad->Location = System::Drawing::Point(97,145);
//		textBoxCOMPuerto->Location = System::Drawing::Point(97,103);
//		buttonCOMIniciar->Location= System::Drawing::Point(90,201);
//		buttonCOMIniciar->Text="Connect";
//		buttonCOMIniciar->Size = System::Drawing::Size(110,23);
//		comboBox1->Visible=true;
//		textBoxCOMPuerto->Visible=true;
//		textBoxCOMVelocidad->Visible=true;
//		rectangleShape1->Visible=true;
//		textBoxCOMPuerto->Text=gcnew String(c[0]->getChar());
//		textBoxCOMVelocidad->Text=Convert::ToString(c[0]->getunsigned());
//	}
//	void Interfaz05()
//	{
//		labelConnectionType->Location=Point(61,4);
//		rectangleShape1->Visible=false;
//		if(c[0]->GetType()==ConnectionType::TCP_IP_SERVER)
//		{
//			 comboBox1->Visible=false;
//			 textBoxCOMPuerto->Visible=false;
//			 textBoxCOMVelocidad->Visible=false;
//	         buttonCOMIniciar->Text="Disconnect";
//			 buttonCOMIniciar->Location = System::Drawing::Point(205,226);
//			 buttonCOMIniciar->Size = System::Drawing::Size(71, 23);
//			 labelConnectionType->Visible=true;
//			 labelConnectionType->Text=comboBox1->Text;
//			 buttonSocketIniciar->Visible=true;
//		}
//		else
//			Interfaz1();
//
//	}
//	void Interfaz1()
//		 {
//			 cont=0;
//			 labelError->Visible=false;
//			 buttonSend->Visible=true;
//			 buttonCOMIniciar->Text="Disconnect";
//			 buttonCOMIniciar->Location = System::Drawing::Point(205,226);
//			 buttonCOMIniciar->Size = System::Drawing::Size(71, 23);
//			 comboBox1->Visible=false;
//			 checkBoxAutoSend->Checked=false;
//			 textBoxAutoS->Visible=false;
//			 labelConnectionType->Visible=true;
//			 labelConnectionType->Text=comboBox1->Text;
//			 radioButtonNormal->Location = System::Drawing::Point(102,70);
//			 radioButtonESE_GRS->Location = System::Drawing::Point(102,47);
//			 textBoxCOMPuerto->Visible=true;
//			 textBoxCOMVelocidad->Visible=true;
//			 radioButtonESE_GRS->Visible=true;
//			 radioButtonNormal->Visible=true;
//			 ActivateDesactiveRadButt0(true);
//			 labelCharUnsignedConnection->Text=gcnew String(c[0]->getChar())+"::"+Convert::ToString(c[0]->getunsigned());
//			 labelCharUnsignedConnection->Visible=true;
//			 checkBoxAutoVerif->Visible=true;
//			 checkBoxAutoSend->Visible=true;
//		 }
//	void  ActivateDesactiveRadButt0(bool ActiveDesact)
//	{
//	 if(ActiveDesact)
//		{
//	     buttonRedireccionar->Visible=true;
//	     checkBoxDraw->Visible=true;
//		 checkBoxCode->Visible=true;
//		  textBoxCOMVelocidad->Visible=true;
//		 textBoxCOMPuerto->Text="00000001";
//		 textBoxCOMVelocidad->Text="00000001"; 
//		 textBoxCOMPuerto->Location = System::Drawing::Point(97,110);
//         textBoxCOMVelocidad->Location = System::Drawing::Point(97,136);
//		 this->textBoxCOMPuerto->MaxLength = 8;
//		 this->textBoxCOMVelocidad->MaxLength = 8;
//		}
//	 else
//	 {
//	    buttonRedireccionar->Visible=false;
//	    checkBoxDraw->Visible=false;
//		checkBoxCode->Visible=false;
//	 }
//}
//	void  ActivateDesactiveRadButt1(bool ActiveDesact)
//	{
//	 if(ActiveDesact)
//  	 {
//		 textBoxCOMPuerto->Location = System::Drawing::Point(97,103);
//		 textBoxCOMVelocidad->Location = System::Drawing::Point(97,145);
//		 textBoxCOMPuerto->Text="DataToSend";
//		 textBoxCOMVelocidad->Visible=false;
//	 }
//	}
//	char*ToBinary(const char*HigthByte,const char*LowByte)
//	{
//		if(strlen(HigthByte)!=8||strlen(LowByte)!=8)
//		{
//			System::Windows::Forms::MessageBox::Show("Error:Must be 8 characters by Byte");
//			return NULL;
//		}
//		bool errHigth0=true,errLow0=true;
//		for(unsigned i=0;i<8;i++)
//		{
//			if((HigthByte[i]!='1'&&HigthByte[i]!='0')||(LowByte[i]!='1'&&LowByte[i]!='0'))
//			{
//			    System::Windows::Forms::MessageBox::Show("Error:Must be all characters 0 or 1");
//				return NULL;
//			}
//			if(HigthByte[i]=='1'&&errHigth0)
//				errHigth0=false;
//			if(LowByte[i]=='1'&&errLow0)
//				errLow0=false;
//		}
//		if(errHigth0||errLow0)
//		{
//			System::Windows::Forms::MessageBox::Show("Error:At least one character must be 1");
//			return NULL;
//		}
//		unsigned multip=1,sumaHigth=0,sumaLow=0;
//
//		for(int i=7;i>=0;i--)
//		{
//			if(HigthByte[i]=='1')
//				sumaHigth+=multip;
//			if(LowByte[i]=='1')
//				sumaLow+=multip;
//			multip*=2;
//		}
//		char*toReturn=new char[3];
//		toReturn[0]=sumaLow;
//		toReturn[1]=sumaHigth;
//		toReturn[2]=0;
//		return toReturn;
//
//	
//	}
//	void SendAuto(){
//	
//		cont++;
//		if(cont==10)
//		{
//			cont=0;
//			buttonAuto_Click(gcnew System::Object,gcnew System::EventArgs);
//		}
//	};
//	void InterfazAutoSend(bool activDesact)
//	{
//		if(activDesact)
//		{
//			 const char*txbAS=context.marshal_as<const char*>(textBoxAutoS->Text);
//			for(unsigned i=0;i<strlen(txbAS);i++)	 
//			{
//				if(!isalnum(txbAS[i]))
//				{
//					System::Windows::Forms::MessageBox::Show("Characters of Interval not valid");
//					textBoxAutoS->Focus();
//					return;
//				}
//			}
//			SendCont=true;
//			buttonSend->Text="Stop";
//			textBoxCOMPuerto->Enabled=false;
//			textBoxCOMVelocidad->Enabled=false;
//			checkBoxAutoSend->Enabled=false;
//			checkBoxDraw->Enabled=false;
//			checkBoxAutoVerif->Enabled=false;
//			checkBoxCode->Enabled=false;
//			radioButtonESE_GRS->Enabled=false;
//			radioButtonNormal->Enabled=false;
//			textBoxAutoS->Enabled=false;
//			buttonAcept->Enabled=false;
//		    buttonCancel->Enabled=false;
//            buttonFocusClick->Enabled=false;
//			buttonNextFocus->Enabled=false;
//			buttonRedireccionar->Enabled=false;
//			timer2->Interval = (int)atoi(txbAS);
//			timer2->Enabled=true;
//		}
//		else
//		{
//			SendCont=false;
//			timer2->Enabled=false;
//			buttonSend->Text="AutoSend";
//			textBoxCOMPuerto->Enabled=true;
//			textBoxCOMVelocidad->Enabled=true;
//			checkBoxAutoSend->Enabled=true;
//			checkBoxDraw->Enabled=true;
//			checkBoxAutoVerif->Enabled=true;
//			checkBoxCode->Enabled=true;
//			buttonAcept->Enabled=true;
//		    buttonCancel->Enabled=true;
//            buttonFocusClick->Enabled=true;
//			buttonNextFocus->Enabled=true;
//			radioButtonESE_GRS->Enabled=true;
//			radioButtonNormal->Enabled=true;
//			textBoxAutoS->Enabled=true;
//		    buttonRedireccionar->Enabled=true;	
//		}
//	}
//	
//private: System::Void radioButton1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
//			 if(radioButtonESE_GRS->Checked)
//			 {
//				 ActivateDesactiveRadButt1(false);
//				 ActivateDesactiveRadButt0(true);
//				 checkBoxAutoVerif->Checked=true;
//				 checkBoxAutoVerif->Visible=true;
//				 buttonAuto->Visible=false;
//				 checkBoxAutoSend->Visible=true;
//				 checkBoxAutoSend->Checked=false;
//				 textBoxAutoS->Visible=false;
//				 checkBoxCode->Checked=false;
//			 }
//			 else if(radioButtonNormal->Checked)
//			 {
//				 textBoxCOMPuerto->Text="Send";
//				 ActivateDesactiveRadButt1(true);
//				 ActivateDesactiveRadButt0(false);
//				 textBoxCOMPuerto->Location = System::Drawing::Point(97,123);
//				 checkBoxAutoVerif->Visible=false;
//				 buttonAuto->Visible=false;
//				 checkBoxAutoSend->Visible=false;
//				 textBoxAutoS->Visible=false;
//				 buttonAcept->Visible=false;
//		         buttonCancel->Visible=false;
//                 buttonFocusClick->Visible=false;
//			     buttonNextFocus->Visible=false;
//			 }
//		 }
//private: System::Void checkBoxCOMPuerto_Click(System::Object^  sender, System::EventArgs^  e) {
//			const char*txb1=context.marshal_as<const char*>(textBoxCOMPuerto->Text);
//			char*a=new char[strlen(txb1)+1];
//			a[strlen(txb1)]=0;
//			for(unsigned i=0;i<strlen(txb1);i++)
//			   a[i]=txb1[i];
//			if(checkBoxDraw->Checked)
//			{
//			   a[6]='1';
//			   textBoxCOMPuerto->Text=gcnew String(a);
//			}
//			else 
//			{
//			   a[6]='0';
//			   textBoxCOMPuerto->Text=gcnew String(a);
//			}
//	}	 
//private: System::Void checkBoxCOMVelocidad_Click(System::Object^  sender, System::EventArgs^  e) {
//			 char*aa="00000001";
//			 char*a=new char[9];
//			 for(unsigned i=0;i<8;i++)
//				 a[i]=aa[i];
//			 a[8]=0;
//			 if(checkBoxCode->Checked)
//			{
//			   textBoxCOMPuerto->Text=gcnew String(a);
//			   a[6]='1';
//			   textBoxCOMVelocidad->Text=gcnew String(a);
//		 	   buttonAcept->Visible=true;
//		       buttonCancel->Visible=true;
//               buttonFocusClick->Visible=true;
//			   buttonNextFocus->Visible=true;
//			}
//			else 
//			{
//			   textBoxCOMPuerto->Text=gcnew String(a);
//			   a[6]='0';
//			   textBoxCOMVelocidad->Text=gcnew String(a);
//			   textBoxCOMPuerto->Text=gcnew String(a);
//			   buttonAcept->Visible=false;
//		       buttonCancel->Visible=false;
//               buttonFocusClick->Visible=false;
//			   buttonNextFocus->Visible=false;
//			}
//		 }
//private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
//			 char*s="00000001";
//			 char*s1="00000111";
//			 char*toSend=ToBinary(s,s1);
//			 if(toSend!=NULL)
//			 {
//				 c[0]->Trasmitir(toSend);
//				 cont=0;
//			 }
//		 }
//private: System::Void buttonSend_Click(System::Object^  sender, System::EventArgs^  e) {
//			 if(checkBoxAutoSend->Checked==false)
//			 {
//			    const char*txb1=context.marshal_as<const char*>(textBoxCOMPuerto->Text);
//			    if(radioButtonESE_GRS->Checked)
//			    {
//				   const char*txb2=context.marshal_as<const char*>(textBoxCOMVelocidad->Text);
//			       char*ToSend=ToBinary(txb1,txb2);
//			       if(ToSend!=NULL)
//			       {
//				    c[0]->Trasmitir(ToSend);
//				     if(checkBoxAutoVerif->Checked)
//					   SendAuto();
//			       }
//			    }
//			    else if(radioButtonNormal->Checked)
//			    {
//				  c[0]->Trasmitir((char*)txb1);
//			    }
//			 }
//			 else
//			 {
//				 if(SendCont==false)
//					 InterfazAutoSend(true);
//				 else
//					InterfazAutoSend(false);
//			 }
//
//		 }
//private: System::Void textBoxCOMIniciarConnection_TextChanged(System::Object^  sender, System::EventArgs^  e) {
//			 if(Interfaz==1&&radioButtonESE_GRS->Checked)
//			 {
//				 if(textBoxCOMPuerto->TextLength!=8)
//				 {
//					 buttonSend->Enabled=false;
//					 txb1OK=false;
//				 }
//			     else
//				 {
//					 bool err0=true;;
//					 for(unsigned i=0;i<8;i++)
//					 {	 
//						 if(textBoxCOMPuerto->Text[i]=='1'&&err0)
//							 err0=false;
//						 if(textBoxCOMPuerto->Text[i]!='1'&&textBoxCOMPuerto->Text[i]!='0')
//						 {
//							  buttonSend->Enabled=false; 
//							  txb1OK=false;
//							  return;
//						 }
//				     }
//					 if(err0)
//					 {
//						 buttonSend->Enabled=false; 
//						 txb1OK=false;
//						 return;
//					 }
//					 txb1OK=true;
//					 if(buttonSend->Enabled==false&&txb2OK)
//					    buttonSend->Enabled=true;
//					 if(textBoxCOMPuerto->Text[6]=='1')
//					    checkBoxDraw->Checked=true;
//				     else
//			            checkBoxDraw->Checked=false;
//				 }
//
//				 
//			 }
//		 }
//private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
//			 if(Interfaz==1&&radioButtonESE_GRS->Checked)
//			 {
//				 if(textBoxCOMVelocidad->TextLength!=8)
//				 {
//					 buttonSend->Enabled=false;
//					 txb2OK=false;
//				 }
//				 else 
//				 {
//					  bool err0=true;;
//					 for(unsigned i=0;i<8;i++)
//					 {	 
//						 if(textBoxCOMVelocidad->Text[i]=='1'&&err0)
//							 err0=false;
//						 if(textBoxCOMVelocidad->Text[i]!='1'&&textBoxCOMVelocidad->Text[i]!='0')
//						 {
//							  buttonSend->Enabled=false; 
//							  txb2OK=false;
//							  return;
//						 }
//				     }
//					 if(err0)
//					 {
//						 buttonSend->Enabled=false; 
//						 txb2OK=false;
//						 return;
//					 }
//					 txb2OK=true;
//					 if(buttonSend->Enabled==false&&txb1OK)
//					 {
//					    buttonSend->Enabled=true;
//					 }
//					 if(textBoxCOMVelocidad->Text[6]=='1')
//					    checkBoxCode->Checked=true;
//				     else
//			            checkBoxCode->Checked=false;
//				 }
//
//				 
//			 }
//		 }
//private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
//		    // char*SelectThreadExtern=c[0]->PricipalAction();
//			 if(c[0]->Error())
//			 {
//				 labelError->Text=gcnew String(c[0]->ErrorStr());
//				 System::Windows::Forms::MessageBox::Show(labelError->Text);
//			 }
//			 else
//			    Interfaz1();
//			 timer1->Enabled=false;	 
//
//		 }
//private: System::Void button2_Click_1(System::Object^  sender, System::EventArgs^  e) {
//			 timer1->Enabled=true;
//			 buttonSocketIniciar->Visible=false;
//		 }
//private: System::Void buttonAuto_Click(System::Object^  sender, System::EventArgs^  e) {
//			 char*s="00000001";
//			 char*s1="00000100";
//			 char*toSend=ToBinary(s,s1);
//			 if(toSend!=NULL)
//				 c[0]->Trasmitir(toSend);
//		 }
//private: System::Void checkBoxAuto_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
//			 if(checkBoxAutoVerif->Checked) 
//				 buttonAuto->Visible=false;
//			 else
//				 buttonAuto->Visible=true;
//		 }
//private: System::Void checkBoxAutoSend_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
//			 if(checkBoxAutoSend->Checked)
//			 {
//				 textBoxAutoS->Visible=true;
//				 buttonSend->Text="AutoSend";
//			 }
//			 else
//			 {
//				 textBoxAutoS->Visible=false;
//				 buttonSend->Text="Send";
//			 }
//		 }
//private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
//			 const char*txb1=context.marshal_as<const char*>(textBoxCOMPuerto->Text);
//			 const char*txb2=context.marshal_as<const char*>(textBoxCOMVelocidad->Text);
//			 char*ToSend=ToBinary(txb1,txb2);
//			 if(ToSend!=NULL)
//			    {
//				   c[0]->Trasmitir(ToSend);
//				   SendAuto();
//			    }
//		 }
//private: System::Void buttonNextFocus_Click(System::Object^  sender, System::EventArgs^  e) {
//			 char*s="00000001";
//			 char*s1="00001011";
//			 char*toSend=ToBinary(s,s1);
//			 if(toSend!=NULL)
//			 {
//				 c[0]->Trasmitir(toSend);
//				 SendAuto();
//			 }
//		 }
//private: System::Void buttonFocusClick_Click(System::Object^  sender, System::EventArgs^  e) {
//			 char*s="00000001";
//			 char*s1="00001111";
//			 char*toSend=ToBinary(s,s1);
//			 if(toSend!=NULL)
//			 {
//				 c[0]->Trasmitir(toSend);
//				 SendAuto();
//			 }
//		 }
//private: System::Void buttonAcept_Click(System::Object^  sender, System::EventArgs^  e) {
//			 char*s="00000001";
//			 char*s1="00010011";
//			 char*toSend=ToBinary(s,s1);
//			 if(toSend!=NULL)
//			 {
//				 c[0]->Trasmitir(toSend);
//				 SendAuto();
//			 }
//		 }
//private: System::Void buttonCancel_Click(System::Object^  sender, System::EventArgs^  e) {
//			 char*s="00000001";
//			 char*s1="00010111";
//			 char*toSend=ToBinary(s,s1);
//			 if(toSend!=NULL)
//			 {
//				 c[0]->Trasmitir(toSend);
//				 SendAuto();
//			 }
//		 }
public:
/////////////////////////////////////////////label///////////////////////////////////////////////////////////
private: System::Void labelSocketAddrTabControl2_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
			 if(c[0]->ActualizIP())
			 {
				 string s=c[0]->getChar();
				 s+=":";
				 s+=to_string(c[0]->getunsigned());
				 labelSocketAddrTabControl2->Text=gcnew String(s.c_str());
			 }
		 }
private: System::Void labelSocketPuenteTabControl3_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
			 if(c[0]->ActualizIP())
			 {
				 string s=c[0]->getChar();
				 s+=":";
				 s+=to_string(c[0]->getunsigned());
				 labelSocketPuenteTabControl3->Text=gcnew String(s.c_str());
			 }
		 }
//////////////////////////////////////////////Button//////////////////////////////////////////////////////////
private: System::Void ButtonIniciarConnection_Click(System::Object^  sender, System::EventArgs^  e) {
			 CerrarTodasConexiones();
			 if(tabControl1->SelectedIndex==1)
			 {
				 c=new Connection*[1]();
				 c[0]=new PuertoSerie();
				 const char*txb1=context.marshal_as<const char*>( textBoxCOMPuerto->Text);
				 const char*txb2=context.marshal_as<const char*>(textBoxCOMVelocidad->Text);
				 c[0]->inicializa(txb1,atol(txb2));
			 }
			 else if(tabControl1->SelectedIndex==2)
			 {
				 c=new Connection*[1]();
				 c[0]=new Socket_Client();
				 const char*txb1=context.marshal_as<const char*>( comboBox1->Text);
				 const char*txb2=context.marshal_as<const char*>(comboBox2->Text);
				 c[0]->inicializa(txb1,atol(txb2));
			 }
			 else if(tabControl1->SelectedIndex==4)
			 {
				 c=new Connection*[4]();
				 c[0]=new Socket_Server();
				 const char*txb3=context.marshal_as<const char*>( comboBoxSocketIP->Text);
				 const char*txb4=context.marshal_as<const char*>(textBoxSocketPuerto->Text);
				 c[0]->inicializa(txb3,atol(txb4));
			 }
			 else
				 return;
			 if(!c[0]->Error())
			 {
				 if(tabControl1->SelectedIndex==1)
				 {
					 COM=true;
					 Escenario2();
				 }
				 else if(tabControl1->SelectedIndex==2)
				 {
					 char toSend[3];
					toSend[0]=(char)35;
					toSend[1]=(char)1;
					toSend[2]=0;
					c[0]->Trasmitir(toSend);
					fd_set descriptoresLectura;
					struct timeval tv;
					tv.tv_sec=3;
					tv.tv_usec=55555;
					FD_ZERO(&descriptoresLectura);
					FD_SET(c[0]->GetSocket(),&descriptoresLectura);

					select(c[0]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
					bool err=true;
					char*ToREciv;
					if(FD_ISSET(c[0]->GetSocket(),&descriptoresLectura))
					{
							ToREciv=c[0]->Recibir();
							if(ToREciv!=NULL)
								if(ToREciv[0]==(char)35)
									err=false;
					}
					if(err)
					{
						System::Windows::Forms::MessageBox::Show("SocketCliente_ESE: No Autenticado como ESE");
						 Socket_Cliente=true;
						 c[0]->CloseConnection();
						return;
					}
					 Socket_Cliente=true;
					 Escenario6();
				 }
				 else if(tabControl1->SelectedIndex==4)
				 {
					th=gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(SelectThreadExtern));
					th->Start();
					c[3]=new Socket_Client();
					if(!c[3]->inicializa(c[0]->getChar(),c[0]->getunsigned()))
					{
						string s("SocketCliente_ESE:");
						s+=c[3]->ErrorStr();
						System::Windows::Forms::MessageBox::Show(gcnew System::String(s.c_str()));
					}
					char toSend[3];
					toSend[0]=(char)35;
					toSend[1]=(char)1;
					toSend[2]=0;
					c[3]->Trasmitir(toSend);
					fd_set descriptoresLectura;
					struct timeval tv;
					tv.tv_sec=3;
					tv.tv_usec=55555;
					FD_ZERO(&descriptoresLectura);
					FD_SET(c[3]->GetSocket(),&descriptoresLectura);

					select(c[3]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
					bool err=true;
					char*ToREciv;
					if(FD_ISSET(c[3]->GetSocket(),&descriptoresLectura))
					{
							ToREciv=c[3]->Recibir();
							if(ToREciv!=NULL)
								if(ToREciv[0]==(char)35)
									err=false;
					}
					if(err)
					{
						System::Windows::Forms::MessageBox::Show("SocketCliente_ESE: No Autenticado como ESE");
					}
					SocketServer=true;
					timer1->Enabled=true;
					Escenario1();
				 }
			 }
			 else
			 {
				 System::Windows::Forms::MessageBox::Show(System::String(c[0]->ErrorStr()).ToString());
			 }
		 }
private: System::Void buttonRedireccionar_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(COM_Soket||SocketServer)
				 c[3]->Trasmitir(ToBinary("00000001","00000111"),NULL,true);
			 else
				c[0]->Trasmitir(ToBinary("00000001","00000111"),NULL,true);
			 contVerif=0;
		 }
private: System::Void buttonSocketEnviarTabControl2_Click(System::Object^  sender, System::EventArgs^  e) {
			 const char*txb1=context.marshal_as<const char*>( textBoxSocketHightByteTabControl2->Text);
			 const char*txb2=context.marshal_as<const char*>(textBoxSocketLowByteTabControl2->Text);
			 if(COM_Soket||SocketServer)
				c[3]->Trasmitir(ToBinary(txb1,txb2),NULL,true);
			  else
				c[0]->Trasmitir(ToBinary(txb1,txb2),NULL,true);
			 if(strcmp(txb2,"00000111"))
				Verific();
		 }
private: System::Void buttonSocketFocusTabControl2_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(COM_Soket||SocketServer)
				c[3]->Trasmitir(ToBinary("00000001","00001011"),NULL,true);
			  else
				c[0]->Trasmitir(ToBinary("00000001","00001011"),NULL,true);
			  Verific();
		 }
private: System::Void buttonSocketAceptFocusTabControl2_Click(System::Object^  sender, System::EventArgs^  e) {
			  if(COM_Soket||SocketServer)
				c[3]->Trasmitir(ToBinary("00000001","00001111"),NULL,true);
			 else
				c[0]->Trasmitir(ToBinary("00000001","00001111"),NULL,true);
			  Verific();
		 }
private: System::Void buttonSocketAceptButtonTabControl2_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(COM_Soket||SocketServer)
				c[3]->Trasmitir(ToBinary("00000001","00010011"),NULL,true);
			 else
				c[0]->Trasmitir(ToBinary("00000001","00010011"),NULL,true);
			  Verific();
		 }
private: System::Void buttonSocketCancelButtonTabControl2_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(COM_Soket||SocketServer)
				c[3]->Trasmitir(ToBinary("00000001","00010111"),NULL,true);
			 else
			  c[0]->Trasmitir(ToBinary("00000001","00010111"),NULL,true);
			  Verific();
		 }
private: System::Void buttonSocketDisconectTabControl2_Click(System::Object^  sender, System::EventArgs^  e) {
			 CerrarTodasConexiones();
			 c=new Connection*[1]();
		 }
private: System::Void buttonInitConecctionPuente_Click(System::Object^  sender, System::EventArgs^  e) {
 
			 CerrarTodasConexiones();
			 c=new Connection*[5];
			 c[0]=new Socket_Server();
			 c[3]=new Socket_Client();
			 c[4]=new PuertoSerie();
			 const char*txb1=context.marshal_as<const char*>( comboBoxSocketIPPuente->Text);
			 const char*txb2=context.marshal_as<const char*>(textBoxSocketPuertoPuente->Text);
			 const char*txb3=context.marshal_as<const char*>( textBoxCOMPuertoPuente->Text);
			 const char*txb4=context.marshal_as<const char*>(textBoxCOMVelocidadPuente->Text);
			 if(!c[4]->inicializa(txb3,atol(txb4)))
			 {
				 System::Windows::Forms::MessageBox::Show(System::String(c[4]->ErrorStr()).ToString());
				 this->rectangleShape1->BackColor = System::Drawing::Color::Red;
				 return;
			 }
			 this->rectangleShape1->BackColor = System::Drawing::Color::White;
			 if(!c[0]->inicializa(txb1,atol(txb2)))
			 {
				 System::Windows::Forms::MessageBox::Show(System::String(c[0]->ErrorStr()).ToString());
				 this->rectangleShape2->BackColor = System::Drawing::Color::Red;
				 return;
			 }
			 if(!c[3]->inicializa(c[0]->getChar(),atol(txb2)))
			 {
				 System::Windows::Forms::MessageBox::Show(System::String(c[3]->ErrorStr()).ToString());
				 this->rectangleShape1->BackColor = System::Drawing::Color::Yellow;
				 this->rectangleShape2->BackColor = System::Drawing::Color::Yellow;
				 return;
			 }
			 this->rectangleShape2->BackColor = System::Drawing::Color::Green;
			 COM_Soket=true;
			 timer2->Enabled=true;
			 th=gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(SelectThreadExtern));
			 th->Start();
			 char toSend[3];
			 toSend[0]=(char)35;
			 toSend[1]=(char)1;
			 toSend[2]=0;
			 c[3]->Trasmitir(toSend);
			 fd_set descriptoresLectura;
		 	 struct timeval tv;
			 tv.tv_sec=3;
		 	 tv.tv_usec=55555;
			 FD_ZERO(&descriptoresLectura);
			 FD_SET(c[3]->GetSocket(),&descriptoresLectura);
			 select(c[3]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
			 bool err=true;
			 char*toReciv;
			 if(FD_ISSET(c[3]->GetSocket(),&descriptoresLectura))
			 {
				 toReciv=c[3]->Recibir();
				 if(toReciv!=NULL)
				 {
					if(toReciv[0]==(char)35)
				    {
						err=false;
				    }
			    }
			 }
			 if(err)
			 {
				 System::Windows::Forms::MessageBox::Show(gcnew System::String("Error al acceder como ESE_GRS COM"));
				 this->rectangleShape1->BackColor = System::Drawing::Color::Yellow;
				 this->rectangleShape2->BackColor = System::Drawing::Color::Yellow;
				 buttonDesconectarPuente_Click(gcnew System::Object,gcnew System::EventArgs);
				 return;
			 }
			 timer1->Enabled=true; 
			 Escenario3();
		 }
private: System::Void buttonDesconectarPuente_Click(System::Object^  sender, System::EventArgs^  e) {
			 CerrarTodasConexiones();
			 c=new Connection*[1]();
			 Escenario0();
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 VistaDeCarga();
		 }
private: System::Void button21_Click(System::Object^  sender, System::EventArgs^  e) {
			 VistaClientes(0);
		 }
private: System::Void button22_Click(System::Object^  sender, System::EventArgs^  e) {
			  VistaClientes(1);
		 }
private: System::Void button23_Click(System::Object^  sender, System::EventArgs^  e) {
			  VistaClientes(2);
		 }
private: System::Void button24_Click(System::Object^  sender, System::EventArgs^  e) {
			  VistaClientes(3);
		 }
private: System::Void button25_Click(System::Object^  sender, System::EventArgs^  e) {
			  VistaClientes(4);
		 }
private: System::Void button26_Click(System::Object^  sender, System::EventArgs^  e) {
			  VistaClientes(5);
		 }
private: System::Void button27_Click(System::Object^  sender, System::EventArgs^  e) {
			  VistaClientes(6);
		 }
private: System::Void button28_Click(System::Object^  sender, System::EventArgs^  e) {
			  VistaClientes(7);
		 }
private: System::Void button29_Click(System::Object^  sender, System::EventArgs^  e) {
			  VistaClientes(8);
		 }
private: System::Void button30_Click(System::Object^  sender, System::EventArgs^  e) {
			  VistaClientes(9);
		 }
private: System::Void buttonDesconectar_Click(System::Object^  sender, System::EventArgs^  e) {
			 c[0]->SocketServer_QuitarUser(contClienteVista);
			 c[0]->SetBoolCerrarSocket(true);
			 c[0]->SocketServer_CerrarSocketByIndex(contClienteVista);
			 buttonAcceso->BackColor=System::Drawing::Color::Transparent;
			 flowLayoutPanel1->BackColor=System::Drawing::Color::Transparent;
		 }
private: System::Void buttonAcceso_Click(System::Object^  sender, System::EventArgs^  e) {
			 c[0]->SocketServer_PonerUser(contClienteVista);
		 }
private: System::Void MybuttonConnectarHost_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(SocketServer||COM_Soket)
			 {
				 CerrarWebPuente();
				 c[1]=new WebSocket_Client();
				 c[2]=new Socket_Client();
				 const char*txb1=context.marshal_as<const char*>( comboBoxHost->Text);
				 const char*txb2=context.marshal_as<const char*>(textBoxHostPuerto->Text);
				 if(!c[1]->inicializa(txb1,atol(txb2)))
				 {
					 System::Windows::Forms::MessageBox::Show(System::String(c[1]->ErrorStr()).ToString());
					 return;
				 }
				 if(!c[2]->inicializa(c[0]->getChar(),c[0]->getunsigned()))
				 {
					 c[1]->CloseConnection();
					 System::Windows::Forms::MessageBox::Show(System::String(c[2]->ErrorStr()).ToString());
					 return;
				 }
				 char toSend[3];
				 toSend[0]=(char)107;
				 toSend[1]=(char)1;
				 toSend[2]=0;
				 c[1]->Trasmitir(toSend);
				 fd_set descriptoresLectura;
				 struct timeval tv;
				 tv.tv_sec=3;
		 		 tv.tv_usec=55555;
				 FD_ZERO(&descriptoresLectura);
				 FD_SET(c[1]->GetSocket(),&descriptoresLectura);
				 select(c[1]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
				 bool err=true;
				 char*toReciv;
				 if(FD_ISSET(c[1]->GetSocket(),&descriptoresLectura))
				 {
					 toReciv=c[1]->Recibir();
					 if(toReciv!=NULL)
						 if(toReciv[0]==(char)107)
				 			err=false;
				 }
				 if(err)
				 {
					System::Windows::Forms::MessageBox::Show("SocketCliente_WEBPuente: No Autenticado como WebPuente en Web");
					c[1]->CloseConnection();
					c[2]->CloseConnection();
					return;
				 }
				 c[2]->Trasmitir(toSend);
				 FD_ZERO(&descriptoresLectura);
				 FD_SET(c[2]->GetSocket(),&descriptoresLectura);
				 select(c[2]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
				 err=true;
				 if(FD_ISSET(c[2]->GetSocket(),&descriptoresLectura))
				 {
					 toReciv=c[2]->Recibir();
					 if(toReciv!=NULL)
						 if(toReciv[0]==(char)107)
				 			err=false;
				 }
				 if(err)
				 {
					System::Windows::Forms::MessageBox::Show("SocketCliente_WEBPuente: No Autenticado como WebPuente en ServerSocket");
					c[1]->CloseConnection();
					c[2]->CloseConnection();
					return;
				 }
				 
				toSend[0]=(char)99;
				c[1]->Trasmitir(toSend);
				FD_ZERO(&descriptoresLectura);
				FD_SET(c[1]->GetSocket(),&descriptoresLectura);
				select(c[1]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
				err=true;
				if(FD_ISSET(c[1]->GetSocket(),&descriptoresLectura))
				{
					toReciv=c[1]->Recibir();
					if(toReciv!=NULL)
						if(toReciv[0]==(char)99)
						{
							err=false;
							switch (toReciv[1])
							{
							case 4:
								if(c[0]->SocketServer_ClientUserIndex()!=-1)
								{
									System::Windows::Forms::MessageBox::Show("User perdido del ServerSocket");
									c[0]->SocketServer_QuitarOnlyUSER(c[0]->SocketServer_ClientUserIndex());
								}
								toSend[0]=(char)51;
								c[2]->Trasmitir(toSend);
								if(c[0]->SocketServer_ClientESEIndex()!=-1)
								{
									System::Windows::Forms::MessageBox::Show("ESE perdido del ServerSocket");
									c[0]->SocketServer_QuitarOnlyESE(c[0]->SocketServer_ClientESEIndex());
								}
								toSend[0]=(char)35;
								c[2]->Trasmitir(toSend);
								break;
							case 3:
								if(c[0]->SocketServer_ClientESEIndex()!=-1)
								{
									System::Windows::Forms::MessageBox::Show("ESE perdido del ServerSocket");
									c[0]->SocketServer_QuitarOnlyESE(c[0]->SocketServer_ClientESEIndex());
								}
								toSend[0]=(char)35;
								c[2]->Trasmitir(toSend);
								if(c[0]->SocketServer_ClientUserIndex()!=-1)
								{
									bool err1=true;
									toSend[0]=(char)51;
									c[1]->Trasmitir(toSend);
									FD_ZERO(&descriptoresLectura);
									FD_SET(c[1]->GetSocket(),&descriptoresLectura);
									select(c[1]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
									if(FD_ISSET(c[1]->GetSocket(),&descriptoresLectura))
									{
										toReciv=c[1]->Recibir();
										if(toReciv!=NULL)
											if(toReciv[0]==(char)51)
												err1=false;
									}
									if(err1)
									{
										System::Windows::Forms::MessageBox::Show("User perdido del ServerSocket");
										c[0]->SocketServer_QuitarOnlyUSER(c[0]->SocketServer_ClientUserIndex());
									}
								}
								break;
							case 2:
								if(c[0]->SocketServer_ClientUserIndex()!=-1)
								{
									System::Windows::Forms::MessageBox::Show("User perdido del ServerSocket");
									c[0]->SocketServer_QuitarOnlyUSER(c[0]->SocketServer_ClientUserIndex());
								}
								toSend[0]=(char)51;
								c[2]->Trasmitir(toSend);
								if(c[0]->SocketServer_ClientESEIndex()!=-1)
								{
									bool err1=true;
									toSend[0]=(char)35;
									c[1]->Trasmitir(toSend);
									FD_ZERO(&descriptoresLectura);
									FD_SET(c[1]->GetSocket(),&descriptoresLectura);
									select(c[1]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
									if(FD_ISSET(c[1]->GetSocket(),&descriptoresLectura))
									{
										toReciv=c[1]->Recibir();
										if(toReciv!=NULL)
											if(toReciv[0]==(char)35)
												err1=false;
									}
									if(err1)
									{
										System::Windows::Forms::MessageBox::Show("ESE perdido del ServerSocket");
										c[0]->SocketServer_QuitarOnlyESE(c[0]->SocketServer_ClientESEIndex());
									}
								}
								break;
							case 1:
								if(c[0]->SocketServer_ClientESEIndex()!=-1)
								{
									bool err1=true;
									toSend[0]=(char)35;
									c[1]->Trasmitir(toSend);
									FD_ZERO(&descriptoresLectura);
									FD_SET(c[1]->GetSocket(),&descriptoresLectura);
									select(c[1]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
									if(FD_ISSET(c[1]->GetSocket(),&descriptoresLectura))
									{
										toReciv=c[1]->Recibir();
										if(toReciv!=NULL)
											if(toReciv[0]==(char)35)
												err1=false;
									}
									if(err1)
									{
										System::Windows::Forms::MessageBox::Show("ESE perdido del ServerSocket");
										c[0]->SocketServer_QuitarOnlyESE(c[0]->SocketServer_ClientESEIndex());
									}
								}
								if(c[0]->SocketServer_ClientUserIndex()!=-1)
								{
									bool err1=true;
									toSend[0]=(char)51;
									c[1]->Trasmitir(toSend);
									FD_ZERO(&descriptoresLectura);
									FD_SET(c[1]->GetSocket(),&descriptoresLectura);
									select(c[1]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
									if(FD_ISSET(c[1]->GetSocket(),&descriptoresLectura))
									{
										toReciv=c[1]->Recibir();
										if(toReciv!=NULL)
											if(toReciv[0]==(char)51)
												err1=false;
									}
									if(err1)
									{
										System::Windows::Forms::MessageBox::Show("User perdido del ServerSocket");
										c[0]->SocketServer_QuitarOnlyUSER(c[0]->SocketServer_ClientUserIndex());
									}
								}
								break;
							}
						}
				}
				if(err)
				{
					System::Windows::Forms::MessageBox::Show("ERROR en la comunicacion SocketServer-Web");
					c[1]->CloseConnection();
					c[2]->CloseConnection();
					return;
				}

					 
				/////////////////////////////////////////////////////////////////////////////////



				 thWebSocketCliente=gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(ThreadWebSocketClient));
				 thSocketCliente=gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(ThreadSocketClient));
				 thWebSocketCliente->Start();
				 thSocketCliente->Start();
				 WebSocket=true;
				 MiniEscenario4();
			 }
			 else
			 {
				 CerrarTodasConexiones();
				 c=new Connection*[1]();
				 c[0]=new WebSocket_Client();
				 const char*txb1=context.marshal_as<const char*>( comboBoxHost->Text);
				 const char*txb2=context.marshal_as<const char*>(textBoxHostPuerto->Text);
				 if(!c[0]->inicializa(txb1,atol(txb2)))
				 {
					 System::Windows::Forms::MessageBox::Show(System::String(c[0]->ErrorStr()).ToString());
					 return;
				 }
				 char toSend[3];
				 toSend[0]=(char)35;
				 toSend[1]=(char)1;
				 toSend[2]=0;
				 c[0]->Trasmitir(toSend);
				 fd_set descriptoresLectura;
				 struct timeval tv;
				 tv.tv_sec=3;
		 		 tv.tv_usec=55555;
				 FD_ZERO(&descriptoresLectura);
				 FD_SET(c[0]->GetSocket(),&descriptoresLectura);

				 select(c[0]->GetSocket(),&descriptoresLectura,NULL,NULL,&tv);
				 bool err=true;
				 char*toREciv;
				 if(FD_ISSET(c[0]->GetSocket(),&descriptoresLectura))
				 {
					 toREciv=c[0]->Recibir();
						if(toREciv[0]==(char)35)
							err=false;
				 }
				 if(err)
				 {
					System::Windows::Forms::MessageBox::Show("SocketCliente_WEBPuente: No Autenticado como WebPuente");
					c[0]->CloseConnection();
					return;
				 }
				 th=gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(ThreadWeb));
				 th->Start();
				 timer3->Enabled=true;
				 Web=true;
				 Escenario5();

			 }
		 }
private: System::Void MYbuttonDescanectarServerWeb_Click(System::Object^  sender, System::EventArgs^  e) 
{
		CerrarWebPuente();
}
private: System::Void buttonNOAcceso_Click(System::Object^  sender, System::EventArgs^  e) {
			 c[0]->SocketServer_QuitarUser(contClienteVista);
		 }
//////////////////////////////////////////////CheckBox//////////////////////////////////////////////////////////
private: System::Void checkBoxCOMPuerto_Click(System::Object^  sender, System::EventArgs^  e) {
			if(checkBox1COMPuerto->Checked)
				checkBox1COMPuerto->Checked=false;
			else 
				checkBox1COMPuerto->Checked=true;
		 }
private: System::Void checkBoxCOMVelocidad_Click(System::Object^  sender, System::EventArgs^  e) {
		 if(checkBox1COMVelocidad->Checked)
			 checkBox1COMVelocidad->Checked=false;
		else 
			checkBox1COMVelocidad->Checked=true;
		 }
private: System::Void checkBoxSocketIP_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(checkBoxSocketIP->Checked)
				checkBoxSocketIP->Checked=false;
			else 
				checkBoxSocketIP->Checked=true;
		 }
private: System::Void checkBoxSocketPuerto_Click(System::Object^  sender, System::EventArgs^  e) {
		  if(checkBoxSocketPuerto->Checked)
				checkBoxSocketPuerto->Checked=false;
			else 
				checkBoxSocketPuerto->Checked=true;
		 }
private: System::Void checkBoxCOMPuertoPuente_Click(System::Object^  sender, System::EventArgs^  e) {
			  if(checkBoxCOMPuertoPuente->Checked)
				checkBoxCOMPuertoPuente->Checked=false;
			else 
				checkBoxCOMPuertoPuente->Checked=true;
		 }
private: System::Void checkBoxCOMVelocidadPuente_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(checkBoxCOMVelocidadPuente->Checked)
				checkBoxCOMVelocidadPuente->Checked=false;
			else 
				checkBoxCOMVelocidadPuente->Checked=true;
		 }
private: System::Void checkBoxSocketIPPuente_Click(System::Object^  sender, System::EventArgs^  e) {
			 	 if(checkBoxSocketIPPuente->Checked)
				checkBoxSocketIPPuente->Checked=false;
			else 
				checkBoxSocketIPPuente->Checked=true;
		 }
private: System::Void checkBoxSocketPuertoPuente_Click(System::Object^  sender, System::EventArgs^  e) {
			 	 if(checkBoxSocketPuertoPuente->Checked)
				checkBoxSocketPuertoPuente->Checked=false;
			else 
				checkBoxSocketPuertoPuente->Checked=true;
		 }
private: System::Void checkBoxSocketsIPTabControl2_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(checkBoxSocketPuertoTabControl2->Checked)
				checkBoxSocketPuertoTabControl2->Checked=false;
			else 
				checkBoxSocketPuertoTabControl2->Checked=true;
		 }
private: System::Void checkBoxSocketsPuertoTabControl2_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(checkBoxSocketIPTabControl2->Checked)
				checkBoxSocketIPTabControl2->Checked=false;
			else 
				checkBoxSocketIPTabControl2->Checked=true;
		 }
private: System::Void checkBoxSocketDrawTabControl2_Click(System::Object^  sender, System::EventArgs^  e) {
				const char*txb1=context.marshal_as<const char*>(textBoxSocketHightByteTabControl2->Text);
				char*a=new char[strlen(txb1)+1];
				a[strlen(txb1)]=0;
				for(unsigned i=0;i<strlen(txb1);i++)
					a[i]=txb1[i];
				if(textBoxSocketDrawTabControl2->Checked)
				{
					a[6]='1';
					textBoxSocketHightByteTabControl2->Text=gcnew String(a);
				}
				else 
				{
					a[6]='0';
					textBoxSocketHightByteTabControl2->Text=gcnew String(a);
				}
				delete[]a;
		 }
//////////////////////////////////////////////TextBox//////////////////////////////////////////////////////////
private: System::Void textBoxSocketIniciarConnection_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		    checkBoxSocketIP->Checked=false;
			this->checkBoxSocketIP->BackColor = System::Drawing::Color::Transparent;
			this->checkBoxSocketPuerto->BackColor = System::Drawing::Color::Transparent;
			checkBoxSocketPuerto->Checked=false;
			unsigned punt=0;
			unsigned contnum=0;
			bool lastPunt=false;
			try
			{
				if(comboBoxSocketIP->Text==(gcnew String("INADDR_ANY")))
				{
					checkBoxSocketIP->Checked=true;
					this->checkBoxSocketIP->BackColor = System::Drawing::Color::LightGreen;
					throw(true);
				}
				for(unsigned i=0;i<(unsigned)comboBoxSocketIP->Text->Length;i++)
				{
					if(comboBoxSocketIP->Text[comboBoxSocketIP->Text->Length-1]=='.')
						throw(true);
					if(!isdigit(comboBoxSocketIP->Text[i]))
					{
						if(comboBoxSocketIP->Text[i]=='.')
						{
							if(punt==3||lastPunt)
								throw(true);
							punt++;
							contnum=0;
							lastPunt=true;
							continue;
						}
						else
							throw(true);
	
					}
					if(contnum==3)
						throw(true);
					contnum++;
					lastPunt=false;
				}
				if(punt==3)
				{
					checkBoxSocketIP->Checked=true;
					this->checkBoxSocketIP->BackColor = System::Drawing::Color::LightGreen;
				}
			}catch(bool){};
			try
			{
				if(!textBoxSocketPuerto->Text->Length)
					throw(true);
				for(unsigned i=0;i<(unsigned)textBoxSocketPuerto->Text->Length;i++)
					if(!isdigit(textBoxSocketPuerto->Text[i]))
						throw(true);
				checkBoxSocketPuerto->Checked=true;
				this->checkBoxSocketPuerto->BackColor = System::Drawing::Color::LightGreen;
			}catch(bool){};
			if(checkBoxSocketIP->Checked&&checkBoxSocketPuerto->Checked)
				buttonSocketIniciar->Enabled=true;
			else
				buttonSocketIniciar->Enabled=false;
		 }
private: System::Void textBoxCOMIniciarConnection_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			checkBox1COMPuerto->Checked=false;
			this->checkBox1COMPuerto->BackColor = System::Drawing::Color::Transparent;
			this->checkBox1COMVelocidad->BackColor = System::Drawing::Color::Transparent;
			checkBox1COMVelocidad->Checked=false;
			 try
			{ 
				if(textBoxCOMPuerto->Text->Length>3)		 
					 if(textBoxCOMPuerto->Text[0]=='C'||textBoxCOMPuerto->Text[0]=='c')
						 if(textBoxCOMPuerto->Text[1]=='O'||textBoxCOMPuerto->Text[1]=='o')
							 if(textBoxCOMPuerto->Text[2]=='M'||textBoxCOMPuerto->Text[2]=='m')
							 {
								 for(unsigned i=3;i<(unsigned)textBoxCOMPuerto->Text->Length;i++)
									if(!isdigit(textBoxCOMPuerto->Text[i]))
									{
										throw(true);
									}
								 checkBox1COMPuerto->Checked=true;
								 this->checkBox1COMPuerto->BackColor = System::Drawing::Color::Green;	 
							 }
				}catch(bool){}
			try
			{
				if(!textBoxCOMVelocidad->Text->Length)
					throw(true);
				for(unsigned i=0;i<(unsigned)textBoxCOMVelocidad->Text->Length;i++)
					if(!isdigit(textBoxCOMVelocidad->Text[i]))
					{
						throw(true);
					}
				checkBox1COMVelocidad->Checked=true;
				this->checkBox1COMVelocidad->BackColor = System::Drawing::Color::Green;	
			}catch(bool){}
			if(checkBox1COMPuerto->Checked && checkBox1COMVelocidad->Checked)
				buttonCOMIniciar->Enabled=true;
			else
				buttonCOMIniciar->Enabled=false;
		 }
private: System::Void textBoxSocketBytesTabControl2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			checkBoxSocketPuertoTabControl2->Checked=false;
			checkBoxSocketIPTabControl2->Checked=false;
			textBoxSocketDrawTabControl2->Enabled=false;
			this->checkBoxSocketPuertoTabControl2->BackColor = System::Drawing::Color::Transparent;
			this->checkBoxSocketIPTabControl2->BackColor = System::Drawing::Color::Transparent;
			try
			{
				if(textBoxSocketHightByteTabControl2->Text->Length!=8)
					throw(true);
				bool Exit1=false;
				for(unsigned i=0;i<8;i++)
				{
					if(textBoxSocketHightByteTabControl2->Text[i]=='1'&&!Exit1)
						Exit1=true;
					if(textBoxSocketHightByteTabControl2->Text[i]!='1'&&textBoxSocketHightByteTabControl2->Text[i]!='0')
						throw(true);
				}
				if(!Exit1)
					throw(true);
				this->checkBoxSocketPuertoTabControl2->Checked=true;
				this->checkBoxSocketPuertoTabControl2->BackColor = System::Drawing::Color::LightGreen;
				if(textBoxSocketHightByteTabControl2->Text[6]=='1')
					textBoxSocketDrawTabControl2->Checked=true;
				else
					textBoxSocketDrawTabControl2->Checked=false;
			}catch(bool){}
			try
			{
				if(textBoxSocketLowByteTabControl2->Text->Length!=8)
					throw(true);
				bool Exit1=false;
				for(unsigned i=0;i<8;i++)
				{
					if(textBoxSocketLowByteTabControl2->Text[i]=='1'&&!Exit1)
						Exit1=true;
					if(textBoxSocketLowByteTabControl2->Text[i]!='1'&&textBoxSocketLowByteTabControl2->Text[i]!='0')
						throw(true);
				}
				if(!Exit1)
					throw(true);
				this->checkBoxSocketIPTabControl2->Checked=true;
				this->checkBoxSocketIPTabControl2->BackColor = System::Drawing::Color::LightGreen;
			}catch(bool){}
			if(checkBoxSocketPuertoTabControl2->Checked&&checkBoxSocketIPTabControl2->Checked)
			{
				buttonSocketEnviarTabControl2->Enabled=true;
				textBoxSocketDrawTabControl2->Enabled=true;
			}
			else
			{
				buttonSocketEnviarTabControl2->Enabled=false;
				textBoxSocketDrawTabControl2->Enabled=false;
			}

		 }
private: System::Void textBoxCOMPuente_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			checkBoxCOMPuertoPuente->Checked=false;
			checkBoxCOMVelocidadPuente->Checked=false;
			this->checkBoxCOMPuertoPuente->BackColor = System::Drawing::Color::Transparent;
			this->checkBoxCOMVelocidadPuente->BackColor = System::Drawing::Color::Transparent;
			 try
			{ 
				if(textBoxCOMPuertoPuente->Text->Length>3)		 
					 if(textBoxCOMPuertoPuente->Text[0]=='C'||textBoxCOMPuertoPuente->Text[0]=='c')
						 if(textBoxCOMPuertoPuente->Text[1]=='O'||textBoxCOMPuertoPuente->Text[1]=='o')
							 if(textBoxCOMPuertoPuente->Text[2]=='M'||textBoxCOMPuertoPuente->Text[2]=='m')
							 {
								 for(unsigned i=3;i<(unsigned)textBoxCOMPuertoPuente->Text->Length;i++)
									if(!isdigit(textBoxCOMPuertoPuente->Text[i]))
									{
										throw(true);
									}
								 checkBoxCOMPuertoPuente->Checked=true;
								 this->checkBoxCOMPuertoPuente->BackColor = System::Drawing::Color::Green;	 
							 }
				}catch(bool){}
			try
			{
				if(!textBoxCOMVelocidadPuente->Text->Length)
					throw(true);
				for(unsigned i=0;i<(unsigned)textBoxCOMVelocidadPuente->Text->Length;i++)
					if(!isdigit(textBoxCOMVelocidadPuente->Text[i]))
					{
						throw(true);
					}
				checkBoxCOMVelocidadPuente->Checked=true;
				this->checkBoxCOMVelocidadPuente->BackColor = System::Drawing::Color::Green;	
			}catch(bool){}
			if(checkBoxCOMPuertoPuente->Checked&&checkBoxCOMVelocidadPuente->Checked)
				VerifCOM=true;
			else
				VerifCOM=false;
			if(VerifCOM&&VerifSocket)
				buttonInitConecctionPuente->Enabled=true;
			else
				buttonInitConecctionPuente->Enabled=false;
		 }
private: System::Void textBoxSocketPuente_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			checkBoxSocketIPPuente->Checked=false;
			checkBoxSocketPuertoPuente->Checked=false;
			this->checkBoxSocketIPPuente->BackColor = System::Drawing::Color::Transparent;
			this->checkBoxSocketPuertoPuente->BackColor = System::Drawing::Color::Transparent;
			unsigned punt=0;
			unsigned contnum=0;
			bool lastPunt=false;
			try
			{
				if(comboBoxSocketIPPuente->Text==(gcnew String("INADDR_ANY")))
				{
					checkBoxSocketIPPuente->Checked=true;
					this->checkBoxSocketIPPuente->BackColor = System::Drawing::Color::Green;
					throw(true);
				}
				for(unsigned i=0;i<(unsigned)comboBoxSocketIPPuente->Text->Length;i++)
				{
					if(comboBoxSocketIPPuente->Text[comboBoxSocketIPPuente->Text->Length-1]=='.')
						throw(true);
					if(!isdigit(comboBoxSocketIPPuente->Text[i]))
					{
						if(comboBoxSocketIPPuente->Text[i]=='.')
						{
							if(punt==3||lastPunt)
								throw(true);
							punt++;
							contnum=0;
							lastPunt=true;
							continue;
						}
						else
							throw(true);
	
					}
					if(contnum==3)
						throw(true);
					contnum++;
					lastPunt=false;
				}
				if(punt==3)
				{
					checkBoxSocketIPPuente->Checked=true;
					this->checkBoxSocketIPPuente->BackColor = System::Drawing::Color::Green;
				}
			}catch(bool){};
			try
			{
				if(!textBoxSocketPuertoPuente->Text->Length)
					throw(true);
				for(unsigned i=0;i<(unsigned)textBoxSocketPuertoPuente->Text->Length;i++)
					if(!isdigit(textBoxSocketPuertoPuente->Text[i]))
						throw(true);
				checkBoxSocketPuertoPuente->Checked=true;
				this->checkBoxSocketPuertoPuente->BackColor = System::Drawing::Color::Green;
			}catch(bool){};
			if(checkBoxSocketIPPuente->Checked&&checkBoxSocketPuertoPuente->Checked)
				VerifSocket=true;
			else
				VerifSocket=false;
			if(VerifCOM&&VerifSocket)
				buttonInitConecctionPuente->Enabled=true;
			else
				buttonInitConecctionPuente->Enabled=false;

		 }
/////////////////////////////////////////////Timer/////////////////////////////////////////////////////////
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	m2.WaitOne();
	if(timer1->Enabled==false)
	{
		m2.ReleaseMutex();
		return;
	}
	if(c[0]->StatusClient())
	{
		c[0]->ActStatusClient(false);
		unsigned cont=c[0]->GetContClients();
		String^s=gcnew String("Clientes: ");
		String^s1=cont.ToString();
		s+=s1;
		labelSocketClientesTabControl2->Visible=false;
		buttonAcceso->Enabled=false;
		buttonDesconectar->Enabled=false;
		buttonNOAcceso->Enabled=false;
		buttonAcceso->BackColor=System::Drawing::Color::Transparent;
		buttonDesconectar->BackColor=System::Drawing::Color::Transparent;
		buttonNOAcceso->BackColor=System::Drawing::Color::Transparent;
		flowLayoutPanel1->BackColor=System::Drawing::Color::Transparent;
		rectangleShape30->BackColor=System::Drawing::Color::Transparent;
		rectangleShape31->BackColor=System::Drawing::Color::Transparent;
		button30->Visible=false;
		button30->BackColor=System::Drawing::Color::Transparent;
		button29->Visible=false;
		button29->BackColor=System::Drawing::Color::Transparent;
		button28->Visible=false;
		button28->BackColor=System::Drawing::Color::Transparent;
		button27->Visible=false;
		button27->BackColor=System::Drawing::Color::Transparent;
		button26->Visible=false;
		button26->BackColor=System::Drawing::Color::Transparent;
		button25->Visible=false;
		button25->BackColor=System::Drawing::Color::Transparent;
		button24->Visible=false;
		button24->BackColor=System::Drawing::Color::Transparent;
		button23->Visible=false;
		button23->BackColor=System::Drawing::Color::Transparent;
		button22->Visible=false;
		button22->BackColor=System::Drawing::Color::Transparent;
		button21->Visible=false;
		button21->BackColor=System::Drawing::Color::Transparent;
		unsigned User=c[0]->SocketServer_ClientUserIndex()+1;
		unsigned ESE=c[0]->SocketServer_ClientESEIndex()+1;
		unsigned PuenteWeb=c[0]->SocketServer_ClientPuenteWebIndex()+1;
		if(PuenteWeb!=-1&&PuenteWeb==User)
			rectangleShape30->BackColor=System::Drawing::Color::Lime;
		if(PuenteWeb!=-1&&PuenteWeb==ESE)
			rectangleShape31->BackColor=System::Drawing::Color::Purple;
		switch (cont)
		{
		case 10:
			button30->Visible=true;
		case 9:
			button29->Visible=true;
		case 8:
			button28->Visible=true;
		case 7:
			button27->Visible=true;
		case 6:
			button26->Visible=true;
		case 5:
			button25->Visible=true;
		case 4:
			button24->Visible=true;
		case 3:
			button23->Visible=true;
		case 2:
			button22->Visible=true;
		case 1:
			button21->Visible=true;
		}
		switch (User)
		{
		case 10:
			button30->BackColor=System::Drawing::Color::Lime;
			break;
		case 9:
			button29->BackColor=System::Drawing::Color::Lime;
			break;
		case 8:
			button28->BackColor=System::Drawing::Color::Lime;
			break;
		case 7:
			button27->BackColor=System::Drawing::Color::Lime;
			break;
		case 6:
			button26->BackColor=System::Drawing::Color::Lime;
			break;
		case 5:
			button25->BackColor=System::Drawing::Color::Lime;
			break;
		case 4:
			button24->BackColor=System::Drawing::Color::Lime;
			break;
		case 3:
			button23->BackColor=System::Drawing::Color::Lime;
			break;
		case 2:
			button22->BackColor=System::Drawing::Color::Lime;
			break;
		case 1:
			button21->BackColor=System::Drawing::Color::Lime;
			break;
		}
		switch (ESE)
		{
		case 10:
			button30->BackColor=System::Drawing::Color::Purple;
			break;
		case 9:
			button29->BackColor=System::Drawing::Color::Purple;
			break;
		case 8:
			button28->BackColor=System::Drawing::Color::Purple;
			break;
		case 7:
			button27->BackColor=System::Drawing::Color::Purple;
			break;
		case 6:
			button26->BackColor=System::Drawing::Color::Purple;
			break;
		case 5:
			button25->BackColor=System::Drawing::Color::Purple;
			break;
		case 4:
			button24->BackColor=System::Drawing::Color::Purple;
			break;
		case 3:
			button23->BackColor=System::Drawing::Color::Purple;
			break;
		case 2:
			button22->BackColor=System::Drawing::Color::Purple;
			break;
		case 1:
			button21->BackColor=System::Drawing::Color::Purple;
			break;
		}
		switch (PuenteWeb)
		{
		case 10:
			if(ErrorThWebSocketClient)
				button30->BackColor=System::Drawing::Color::Red;
			else
				button30->BackColor=System::Drawing::Color::Orange;
			break;
		case 9:
			if(ErrorThWebSocketClient)
				button29->BackColor=System::Drawing::Color::Red;
			else
				button29->BackColor=System::Drawing::Color::Orange;
			break;
		case 8:
			if(ErrorThWebSocketClient)
				button28->BackColor=System::Drawing::Color::Red;
			else
				button28->BackColor=System::Drawing::Color::Orange;
			break;
		case 7:
			if(ErrorThWebSocketClient)
				button27->BackColor=System::Drawing::Color::Red;
			else
				button27->BackColor=System::Drawing::Color::Orange;
			break;
		case 6:
			if(ErrorThWebSocketClient)
				button26->BackColor=System::Drawing::Color::Red;
			else
				button26->BackColor=System::Drawing::Color::Orange;
			break;
		case 5:
			if(ErrorThWebSocketClient)
				button25->BackColor=System::Drawing::Color::Red;
			else
				button25->BackColor=System::Drawing::Color::Orange;
			break;
		case 4:
			if(ErrorThWebSocketClient)
				button24->BackColor=System::Drawing::Color::Red;
			else
				button24->BackColor=System::Drawing::Color::Orange;
			break;
		case 3:
			if(ErrorThWebSocketClient)
				button23->BackColor=System::Drawing::Color::Red;
			else
				button23->BackColor=System::Drawing::Color::Orange;
			break;
		case 2:
			if(ErrorThWebSocketClient)
				button22->BackColor=System::Drawing::Color::Red;
			else
				button22->BackColor=System::Drawing::Color::Orange;
			break;
		case 1:
			if(ErrorThWebSocketClient)
				button21->BackColor=System::Drawing::Color::Red;
			else
				button21->BackColor=System::Drawing::Color::Orange;
			break;
		}
		if(CerrarCOM_Web)
		{
			CerrarCOM_Web=false;
			CerrarWebPuente();
		}
		else if(PuenteWeb!=-1)
		{
			if(ErrorThWebSocketClient)
				labelMostrarHost->BackColor=System::Drawing::Color::Red;
			else
				labelMostrarHost->BackColor=System::Drawing::Color::Turquoise;
		}
		


		tabPageSocketClientesTabControl2->Text=s;
		label9->Text=s1;
		m2.ReleaseMutex();
		return;
	}
	m2.ReleaseMutex();
}
private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
			char*Data;
			m1.WaitOne();
			if(!COM_Soket)
			{
				m1.ReleaseMutex();
				return;
			}
			Data=c[4]->Recibir();
			if(Data!=NULL)
			{
				c[3]->Trasmitir(Data);
				VistaDeCarga();
			}
			m1.ReleaseMutex();
			
		}
private: System::Void timer3_Tick(System::Object^  sender, System::EventArgs^  e) {
		if(c[0]->StatusClient())
		{
			if(CerrarCOM_Web)
			{
				CerrarWebPuente();
				return;
			}
			if(ErrorThWebSocketClient)
				MiniEscenario6();
			else
				MiniEscenario7();
			c[0]->ActStatusClient(false);
		}
}
/////////////////////////////////////////////Functions/////////////////////////////////////////////////////////
private:
	void Escenario0(){//main
		tabControl1->Controls->Remove(tabPageWeb);
		tabControl1->Controls->Add(tabPageWeb);
		this->tabControl3->Visible=false;
		this->tabControl2->Visible=false;
		this->tabControl1->Visible=true;
		this->rectangleShape1->BackColor = System::Drawing::Color::White;
		this->rectangleShape2->BackColor = System::Drawing::Color::White;
	}
	void Escenario1()//PuenteSocketServer
			{
				string s=c[0]->getChar();
				s+=":";
				s+=to_string(c[0]->getunsigned());
				labelSocketAddrTabControl2->Text=gcnew String(s.c_str());
				tabControl2->Controls->Remove(tabPageWeb);
				tabControl2->Controls->Add(tabPageWeb);
				tabControl2->Controls->Remove(tabPageSocketClientesTabControl2);
				tabControl2->Controls->Add(tabPageSocketClientesTabControl2);
				this->tabPageSocketServerTabControl2->Text = L"Server";
				labelSocketCOMServerTabControl2->Text=gcnew String(" Puente Web");
				tabPageSocketClientesTabControl2->Text="Clientes";
				label9->Text="0";
				this->tabControl1->Visible=false;
				this->tabControl2->Visible=true;
				this->tabControl3->Visible=false;
				button30->Visible=false;
				button29->Visible=false;
				button28->Visible=false;
				button27->Visible=false;
				button26->Visible=false;
				button25->Visible=false;
				button24->Visible=false;
				button23->Visible=false;
				button22->Visible=false;
				button21->Visible=false;
			};
	void Escenario2(){//COM
		string s=c[0]->getChar();
		s+=":";
		s+=to_string(c[0]->getunsigned());
		labelSocketAddrTabControl2->Text=gcnew String(s.c_str());
		tabControl2->Controls->Remove(tabPageSocketClientesTabControl2);
		tabControl2->Controls->Remove(tabPageWeb);
		this->tabPageSocketServerTabControl2->Text = L"COM";
		labelSocketCOMServerTabControl2->Text=gcnew String("Puerto Serie");
		tabControl1->Visible=false;
		tabControl2->Visible=true;
		tabControl3->Visible=false;
	}
	void Escenario3()//PUNETECOM
	{
		string s=c[0]->getChar();
		s+=":";
		s+=to_string(c[0]->getunsigned());
		labelSocketPuenteTabControl3->Text=gcnew String(s.c_str());
		tabControl3->Controls->Remove(tabPageWeb);
		tabControl3->Controls->Add(tabPageWeb);
		tabControl3->Controls->Remove(tabPageSocketClientesTabControl2);
		tabControl3->Controls->Add(tabPageSocketClientesTabControl2);
		tabPageSocketClientesTabControl2->Text="Clientes";
		contVistaCarga=14;
		label9->Text="0";
		button30->Visible=false;
		button29->Visible=false;
		button28->Visible=false;
		button27->Visible=false;
		button26->Visible=false;
		button25->Visible=false;
		button24->Visible=false;
		button23->Visible=false;
		button22->Visible=false;
		button21->Visible=false;
		tabControl3->Visible=true;
		tabControl2->Visible=false;
		tabControl1->Visible=false;
	};
	void Escenario5()//WEB
	{
		string s=c[0]->getChar();
		s+=":";
		s+=to_string(c[0]->getunsigned());
		labelSocketAddrTabControl2->Text=gcnew String(s.c_str());
		tabControl2->Controls->Remove(tabPageSocketClientesTabControl2);
		labelSocketCOMServerTabControl2->Text=gcnew String("    Web");
		tabControl2->Controls->Remove(tabPageWeb);
		this->tabControl1->Visible=false;
		this->tabControl2->Visible=true;
		this->tabControl3->Visible=false;
	}
	void Escenario6()
	{
		string s=c[0]->getChar();
		s+=":";
		s+=to_string(c[0]->getunsigned());
		labelSocketAddrTabControl2->Text=gcnew String(s.c_str());
		tabControl2->Controls->Remove(tabPageSocketClientesTabControl2);
		tabControl2->Controls->Remove(tabPageWeb);
		this->tabPageSocketServerTabControl2->Text = L"S.Cliente";
		labelSocketCOMServerTabControl2->Text=gcnew String("Socket_Cliente");
		tabControl1->Visible=false;
		tabControl2->Visible=true;
		tabControl3->Visible=false;
	};
	void Escenario7(){
		tabControl1->Controls->Remove(tabPageWeb);
		tabControl1->Controls->Add(tabPageWeb);
		this->tabControl3->Visible=false;
		this->tabControl2->Visible=false;
		this->tabControl1->Visible=true;
		this->rectangleShape1->BackColor = System::Drawing::Color::White;
		this->rectangleShape2->BackColor = System::Drawing::Color::White;
	}
	void MiniEscenario4()
	{
		string s("Conectado:\n");
		s+=c[1]->getChar();
		s+="\n:";
		s+=to_string(c[1]->getunsigned());
		labelMostrarHost->Text=gcnew String(s.c_str());
		comboBoxHost->Visible=false;
		textBoxHostPuerto->Visible=false;
		buttonConnectarHost->Visible=false;
		rectangleShape25->Visible=false;
		labelHost->Visible=false;
		labelPuertoWeb->Visible=false;
		buttonDescanectarServerWeb->Visible=true;
		labelMostrarHost->Visible=true;
		labelMostrarHost->BackColor=System::Drawing::Color::Turquoise;
	}
	void MiniEscenario5()
	{
		comboBoxHost->Visible=true;
		textBoxHostPuerto->Visible=true;
		buttonConnectarHost->Visible=true;
	    rectangleShape25->Visible=true;
		labelHost->Visible=true;
		labelPuertoWeb->Visible=true;
		buttonDescanectarServerWeb->Visible=false;
		labelMostrarHost->Visible=false;
	}
	void MiniEscenario6()
	{
		labelSocketCOMServerTabControl2->BackColor=System::Drawing::Color::Red;
		labelSocketCOMServerTabControl2->Text=gcnew String("Reconectando");

		labelSocketAddrTabControl2->Enabled=false;
		rectangleShape22->Enabled=false;
		checkBoxSocketPuertoTabControl2->Enabled=false;
		checkBoxSocketIPTabControl2->Enabled=false;
		textBoxSocketHightByteTabControl2->Enabled=false;
		textBoxSocketLowByteTabControl2->Enabled=false;
		textBoxSocketDrawTabControl2->Enabled=false;
		buttonSocketEnviarTabControl2->Enabled=false;
		rectangleShape5->Enabled=false;
		buttonSocketFocusTabControl2->Enabled=false;
		buttonSocketAceptFocusTabControl2->Enabled=false;
		buttonSocketRedireccionarTabControl2->Enabled=false;
		buttonSocketCancelButtonTabControl2->Enabled=false;
		buttonSocketAceptButtonTabControl2->Enabled=false;

	}
	void MiniEscenario7()
	{
		labelSocketCOMServerTabControl2->BackColor=System::Drawing::Color::Transparent;
		labelSocketCOMServerTabControl2->Text=gcnew String("   Web");

		labelSocketAddrTabControl2->Enabled=true;
		rectangleShape22->Enabled=true;
		checkBoxSocketPuertoTabControl2->Enabled=true;
		checkBoxSocketIPTabControl2->Enabled=true;
		textBoxSocketHightByteTabControl2->Enabled=true;
		textBoxSocketLowByteTabControl2->Enabled=true;
		textBoxSocketDrawTabControl2->Enabled=true;
		buttonSocketEnviarTabControl2->Enabled=true;
		rectangleShape5->Enabled=true;
		buttonSocketFocusTabControl2->Enabled=true;
		buttonSocketAceptFocusTabControl2->Enabled=true;
		buttonSocketRedireccionarTabControl2->Enabled=true;
		buttonSocketCancelButtonTabControl2->Enabled=true;
		buttonSocketAceptButtonTabControl2->Enabled=true;
	}
	void CerrarCOM()
	{

		if(COM)
		{
			COM=false;
			Escenario0();
		}
	}
	void CerrarSocketCliente()
	{
		if(Socket_Cliente)
		{
			Socket_Cliente=false;
			Escenario7();
		}
	}
	void CerrarWebPuente()
	{
		if(WebSocket)
		{
			WebSocket=false;
			SalirThreadSinError=true;
			ErrorThWebSocketClient=false;
			c[1]->CloseConnection();
			c[2]->CloseConnection();
			thWebSocketCliente->Join();
			thSocketCliente->Join();
			delete c[1];
			delete c[2];
			MiniEscenario5();
		}
		else if(Web)
		{
			Web=false;
			SalirThreadSinError=true;
			c[0]->CloseConnection();
			timer3->Enabled=false;
			th->Join();
			MiniEscenario7();
			Escenario0();
		}
	}
	void CerrarSocketServer()
	{
		if(SocketServer)
		{
			m2.WaitOne();
			timer1->Enabled=false;
			Escenario0();
			SocketServer=false;
			c[0]->CloseConnection();
			th->Join();
			delete c[3];
			m2.ReleaseMutex();
		}
	}
	void CerrarTodasConexiones()
	{
			CerrarCOMPuente();
			CerrarSocketServer();
			CerrarWebPuente();
			CerrarSocketCliente();
			CerrarCOM();
			delete c[0];
			delete[]c;
	}
    void CerrarCOMPuente()
	{
		if(COM_Soket)
		{
			m1.WaitOne();
			m2.WaitOne();
			timer2->Enabled=false;
			timer1->Enabled=false;
			COM_Soket=false;
			c[0]->CloseConnection();
			th->Join();
			delete c[4];
			delete c[3];
			m2.ReleaseMutex();
			m1.ReleaseMutex();
		}
	}
	char*ToBinary(const char*HigthByte,const char*LowByte)
				{
					if(strlen(HigthByte)!=8||strlen(LowByte)!=8)
					{
						System::Windows::Forms::MessageBox::Show("Error:Must be 8 characters by Byte");
						return "NULL";
					}
					bool errHigth0=true,errLow0=true;
					for(unsigned i=0;i<8;i++)
					{
						if((HigthByte[i]!='1'&&HigthByte[i]!='0')||(LowByte[i]!='1'&&LowByte[i]!='0'))
						{
							System::Windows::Forms::MessageBox::Show("Error:Must be all characters 0 or 1");
							return "NULL";
						}
						if(HigthByte[i]=='1'&&errHigth0)
							errHigth0=false;
						if(LowByte[i]=='1'&&errLow0)
							errLow0=false;
					}
					if(errHigth0||errLow0)
					{
						System::Windows::Forms::MessageBox::Show("Error:At least one character must be 1");
						return "NULL";
					}
					unsigned multip=1,sumaHigth=0,sumaLow=0;

					for(int i=7;i>=0;i--)
					{
						if(HigthByte[i]=='1')
							sumaHigth+=multip;
						if(LowByte[i]=='1')
							sumaLow+=multip;
						multip*=2;
					}
					char*toReturn=new char[3];
					toReturn[0]=sumaLow;
					toReturn[1]=sumaHigth;
					toReturn[2]=0;
					return toReturn;
				}
	void Verific()
	{
		contVerif++;
		if(contVerif==10)
		{
			contVerif=0;
			if(COM_Soket||SocketServer)
				c[3]->Trasmitir(ToBinary("00000001","00000100"),NULL,true);
			 else
				c[0]->Trasmitir(ToBinary("00000001","00000100"),NULL,true);
		}
	}
	void VistaDeCarga()
	{
		if(contVistaCarga==14)
			contVistaCarga=0;
		else
			contVistaCarga++;
		switch (contVistaCarga)
		{
		case 0:
			rectangleShape19->BackColor=System::Drawing::Color::Transparent;
			rectangleShape4->BackColor=System::Drawing::Color::Red;
			break;
		case 1:
			rectangleShape4->BackColor=System::Drawing::Color::Transparent;
			rectangleShape6->BackColor=System::Drawing::Color::Red;
			break;
		case 2:
			rectangleShape6->BackColor=System::Drawing::Color::Transparent;
			rectangleShape7->BackColor=System::Drawing::Color::Red;
			break;
		case 3:
			rectangleShape7->BackColor=System::Drawing::Color::Transparent;
			rectangleShape8->BackColor=System::Drawing::Color::Red;
			break;
		case 4:
			rectangleShape8->BackColor=System::Drawing::Color::Transparent;
			rectangleShape9->BackColor=System::Drawing::Color::Red;
			break;
		case 5:
			rectangleShape9->BackColor=System::Drawing::Color::Transparent;
			rectangleShape10->BackColor=System::Drawing::Color::Red;
			break;
		case 6:
			rectangleShape10->BackColor=System::Drawing::Color::Transparent;
			rectangleShape11->BackColor=System::Drawing::Color::Red;
		case 7:
			rectangleShape11->BackColor=System::Drawing::Color::Transparent;
			rectangleShape12->BackColor=System::Drawing::Color::Red;
			break;
		case 8:
			rectangleShape12->BackColor=System::Drawing::Color::Transparent;
			rectangleShape13->BackColor=System::Drawing::Color::Red;
			break;
		case 9:
			rectangleShape13->BackColor=System::Drawing::Color::Transparent;
			rectangleShape14->BackColor=System::Drawing::Color::Red;
			break;
		case 10:
			rectangleShape14->BackColor=System::Drawing::Color::Transparent;
			rectangleShape15->BackColor=System::Drawing::Color::Red;
			break;
		case 11:
			rectangleShape15->BackColor=System::Drawing::Color::Transparent;
			rectangleShape16->BackColor=System::Drawing::Color::Red;
			break;
		case 12:
			rectangleShape16->BackColor=System::Drawing::Color::Transparent;
			rectangleShape17->BackColor=System::Drawing::Color::Red;
			break;
		case 13:
			rectangleShape17->BackColor=System::Drawing::Color::Transparent;
			rectangleShape18->BackColor=System::Drawing::Color::Red;
			break;
		case 14:
			rectangleShape18->BackColor=System::Drawing::Color::Transparent;
			rectangleShape19->BackColor=System::Drawing::Color::Red;
			break;
		}
	}
	void VistaClientes(unsigned i)
	{

			String^s=gcnew String(c[0]->SocketServer_ClienteList(i));
			labelSocketClientesTabControl2->Text=s;
			buttonAcceso->Enabled=false;
			buttonNOAcceso->Enabled=false;
			buttonDesconectar->Enabled=false;
			rectangleShape30->Visible=false;
			rectangleShape31->Visible=false;
			flowLayoutPanel1->BackColor=System::Drawing::Color::Transparent;
			if(c[0]->SocketServer_ClientIsUser(i))
			{
				flowLayoutPanel1->BackColor=System::Drawing::Color::LimeGreen;
				buttonDesconectar->Enabled=true;
				buttonNOAcceso->Enabled=true;
			}
			else if(c[0]->SocketServer_ClientESE(i))
			{
				flowLayoutPanel1->BackColor=System::Drawing::Color::MediumPurple;
				buttonDesconectar->Enabled=true;
			}
			else if(c[0]->SocketServer_ClientAcceso(i))
			{
				buttonAcceso->Enabled=true;
				buttonDesconectar->Enabled=true;
			}
			if(c[0]->SocketServer_ClientPuenteWeb(i))
			{
				buttonAcceso->Enabled=false;
				buttonDesconectar->Enabled=false;
				buttonNOAcceso->Enabled=false;
				rectangleShape30->Visible=true;
				rectangleShape31->Visible=true;
				flowLayoutPanel1->BackColor=System::Drawing::Color::Orange;
			}
			labelSocketClientesTabControl2->Visible=true;
			contClienteVista=i;
	}


private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			checkBox1->Checked=false;
			checkBox2->Checked=false;
			this->checkBox1->BackColor = System::Drawing::Color::Transparent;
			this->checkBox2->BackColor = System::Drawing::Color::Transparent;
			unsigned punt=0;
			unsigned contnum=0;
			bool lastPunt=false;
			try
			{
				for(unsigned i=0;i<(unsigned)comboBox1->Text->Length;i++)
				{
					if(comboBox1->Text[comboBox1->Text->Length-1]=='.')
						throw(true);
					if(!isdigit(comboBox1->Text[i]))
					{
						if(comboBox1->Text[i]=='.')
						{
							if(punt==3||lastPunt)
								throw(true);
							punt++;
							contnum=0;
							lastPunt=true;
							continue;
						}
						else
							throw(true);
	
					}
					if(contnum==3)
						throw(true);
					contnum++;
					lastPunt=false;
				}
				if(punt==3)
				{
					checkBox1->Checked=true;
					this->checkBox1->BackColor = System::Drawing::Color::Green;
				}
			}catch(bool){};
			try
			{
				if(!comboBox2->Text->Length)
					throw(true);
				for(unsigned i=0;i<(unsigned)comboBox2->Text->Length;i++)
					if(!isdigit(comboBox2->Text[i]))
						throw(true);
				checkBox2->Checked=true;
				this->checkBox2->BackColor = System::Drawing::Color::Green;
			}catch(bool){};
			if(checkBox1->Checked&&checkBox2->Checked)
				button1->Enabled=true;
			else
				button1->Enabled=false;

		 }
};
}
//textBoxSocketIPPuentep