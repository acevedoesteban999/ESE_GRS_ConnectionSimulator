#pragma once
#include "Connection.h"
#include <msclr\marshal.h>
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
	public:
		Connection*c;
		unsigned Interfaz,cont;
	private: System::Windows::Forms::Label^  labelError;

	private: System::Windows::Forms::RadioButton^  radioButtonESE_GRS;
	private: System::Windows::Forms::RadioButton^  radioButtonNormal;
	private: System::Windows::Forms::Button^  buttonRedireccionar;
	private: System::Windows::Forms::CheckBox^  checkBoxDraw;
	private: System::Windows::Forms::Label^  labelConnectionType;
	private: System::Windows::Forms::Button^  buttonSend;
	private: System::Windows::Forms::CheckBox^  checkBoxCode;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::RadioButton^  radioButton4;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Label^  labelCharUnsignedConnection;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::CheckBox^  checkBoxAutoVerif;
	private: System::Windows::Forms::Button^  buttonAuto;
	private: Microsoft::VisualBasic::PowerPacks::ShapeContainer^  shapeContainer1;
	private: Microsoft::VisualBasic::PowerPacks::RectangleShape^  rectangleShape1;
	private: System::Windows::Forms::CheckBox^  checkBoxAutoSend;
	private: System::Windows::Forms::TextBox^  textBoxAutoS;
	private: System::Windows::Forms::Timer^  timer2;


	public: 
		msclr::interop::marshal_context context;
		bool SendCont;
		MyForm(void)
		{
			SendCont=false;
			c=new PuertoSerie();
			Interfaz=cont=0;
			InitializeComponent();
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
			c->CloseConnection();
			delete c;
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::ComponentModel::IContainer^  components;


	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->labelError = (gcnew System::Windows::Forms::Label());
			this->radioButtonESE_GRS = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonNormal = (gcnew System::Windows::Forms::RadioButton());
			this->buttonRedireccionar = (gcnew System::Windows::Forms::Button());
			this->checkBoxDraw = (gcnew System::Windows::Forms::CheckBox());
			this->labelConnectionType = (gcnew System::Windows::Forms::Label());
			this->buttonSend = (gcnew System::Windows::Forms::Button());
			this->checkBoxCode = (gcnew System::Windows::Forms::CheckBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->labelCharUnsignedConnection = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->checkBoxAutoVerif = (gcnew System::Windows::Forms::CheckBox());
			this->buttonAuto = (gcnew System::Windows::Forms::Button());
			this->shapeContainer1 = (gcnew Microsoft::VisualBasic::PowerPacks::ShapeContainer());
			this->rectangleShape1 = (gcnew Microsoft::VisualBasic::PowerPacks::RectangleShape());
			this->checkBoxAutoSend = (gcnew System::Windows::Forms::CheckBox());
			this->textBoxAutoS = (gcnew System::Windows::Forms::TextBox());
			this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(90, 214);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(110, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Connect";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(97, 103);
			this->textBox1->MaxLength = 10;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(96, 20);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"COM1";
			this->textBox1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox1_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(97, 145);
			this->textBox2->MaxLength = 10;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(96, 20);
			this->textBox2->TabIndex = 3;
			this->textBox2->Text = L"9600";
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox2_TextChanged);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"SERIAL___PORT", L"TCP_IP_SERVER", L"TCP_IP_CLIENT"});
			this->comboBox1->Location = System::Drawing::Point(90, 57);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(110, 21);
			this->comboBox1->TabIndex = 4;
			this->comboBox1->Text = L"SERIAL___PORT";
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
			this->comboBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::OnTExtChanged);
			// 
			// labelError
			// 
			this->labelError->AutoSize = true;
			this->labelError->Location = System::Drawing::Point(94, 185);
			this->labelError->Name = L"labelError";
			this->labelError->Size = System::Drawing::Size(51, 13);
			this->labelError->TabIndex = 5;
			this->labelError->Text = L"labelError";
			this->labelError->Visible = false;
			// 
			// radioButtonESE_GRS
			// 
			this->radioButtonESE_GRS->AutoSize = true;
			this->radioButtonESE_GRS->Checked = true;
			this->radioButtonESE_GRS->Location = System::Drawing::Point(224, 11);
			this->radioButtonESE_GRS->Name = L"radioButtonESE_GRS";
			this->radioButtonESE_GRS->Size = System::Drawing::Size(75, 17);
			this->radioButtonESE_GRS->TabIndex = 7;
			this->radioButtonESE_GRS->TabStop = true;
			this->radioButtonESE_GRS->Text = L"ESE_GRS";
			this->radioButtonESE_GRS->UseVisualStyleBackColor = true;
			this->radioButtonESE_GRS->Visible = false;
			this->radioButtonESE_GRS->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton1_CheckedChanged);
			// 
			// radioButtonNormal
			// 
			this->radioButtonNormal->AutoSize = true;
			this->radioButtonNormal->Location = System::Drawing::Point(224, 34);
			this->radioButtonNormal->Name = L"radioButtonNormal";
			this->radioButtonNormal->Size = System::Drawing::Size(58, 17);
			this->radioButtonNormal->TabIndex = 8;
			this->radioButtonNormal->Text = L"Normal";
			this->radioButtonNormal->UseVisualStyleBackColor = true;
			this->radioButtonNormal->Visible = false;
			this->radioButtonNormal->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton1_CheckedChanged);
			// 
			// buttonRedireccionar
			// 
			this->buttonRedireccionar->Location = System::Drawing::Point(8, 58);
			this->buttonRedireccionar->Name = L"buttonRedireccionar";
			this->buttonRedireccionar->Size = System::Drawing::Size(20, 20);
			this->buttonRedireccionar->TabIndex = 9;
			this->buttonRedireccionar->Text = L"R";
			this->buttonRedireccionar->UseVisualStyleBackColor = true;
			this->buttonRedireccionar->Visible = false;
			this->buttonRedireccionar->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// checkBoxDraw
			// 
			this->checkBoxDraw->AutoSize = true;
			this->checkBoxDraw->Location = System::Drawing::Point(12, 84);
			this->checkBoxDraw->Name = L"checkBoxDraw";
			this->checkBoxDraw->Size = System::Drawing::Size(51, 17);
			this->checkBoxDraw->TabIndex = 10;
			this->checkBoxDraw->Text = L"Draw";
			this->checkBoxDraw->UseVisualStyleBackColor = true;
			this->checkBoxDraw->Visible = false;
			this->checkBoxDraw->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged);
			// 
			// labelConnectionType
			// 
			this->labelConnectionType->AutoSize = true;
			this->labelConnectionType->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->labelConnectionType->Location = System::Drawing::Point(29, 4);
			this->labelConnectionType->Name = L"labelConnectionType";
			this->labelConnectionType->Size = System::Drawing::Size(233, 25);
			this->labelConnectionType->TabIndex = 11;
			this->labelConnectionType->Text = L"ESE_GRS_SIMULATOR";
			// 
			// buttonSend
			// 
			this->buttonSend->Location = System::Drawing::Point(112, 185);
			this->buttonSend->Name = L"buttonSend";
			this->buttonSend->Size = System::Drawing::Size(65, 23);
			this->buttonSend->TabIndex = 12;
			this->buttonSend->Text = L"Send";
			this->buttonSend->UseVisualStyleBackColor = true;
			this->buttonSend->Visible = false;
			this->buttonSend->Click += gcnew System::EventHandler(this, &MyForm::buttonSend_Click);
			// 
			// checkBoxCode
			// 
			this->checkBoxCode->AutoSize = true;
			this->checkBoxCode->Location = System::Drawing::Point(12, 106);
			this->checkBoxCode->Name = L"checkBoxCode";
			this->checkBoxCode->Size = System::Drawing::Size(51, 17);
			this->checkBoxCode->TabIndex = 13;
			this->checkBoxCode->Text = L"Code";
			this->checkBoxCode->UseVisualStyleBackColor = true;
			this->checkBoxCode->Visible = false;
			this->checkBoxCode->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox2_CheckedChanged);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->radioButton4);
			this->panel1->Controls->Add(this->radioButton3);
			this->panel1->Location = System::Drawing::Point(24, 120);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(64, 69);
			this->panel1->TabIndex = 14;
			this->panel1->Visible = false;
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Location = System::Drawing::Point(3, 26);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(56, 17);
			this->radioButton4->TabIndex = 1;
			this->radioButton4->TabStop = true;
			this->radioButton4->Text = L"Code2";
			this->radioButton4->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Location = System::Drawing::Point(4, 3);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(47, 17);
			this->radioButton3->TabIndex = 0;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"Set0";
			this->radioButton3->UseVisualStyleBackColor = true;
			this->radioButton3->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton3_CheckedChanged);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// labelCharUnsignedConnection
			// 
			this->labelCharUnsignedConnection->AutoSize = true;
			this->labelCharUnsignedConnection->Location = System::Drawing::Point(8, 243);
			this->labelCharUnsignedConnection->Name = L"labelCharUnsignedConnection";
			this->labelCharUnsignedConnection->Size = System::Drawing::Size(150, 13);
			this->labelCharUnsignedConnection->TabIndex = 15;
			this->labelCharUnsignedConnection->Text = L"labelCharUnsignedConnection";
			this->labelCharUnsignedConnection->Visible = false;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(90, 165);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(110, 24);
			this->button2->TabIndex = 16;
			this->button2->Text = L"Wait for a clinet";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Visible = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click_1);
			// 
			// checkBoxAutoVerif
			// 
			this->checkBoxAutoVerif->AutoSize = true;
			this->checkBoxAutoVerif->Checked = true;
			this->checkBoxAutoVerif->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxAutoVerif->Location = System::Drawing::Point(11, 35);
			this->checkBoxAutoVerif->Name = L"checkBoxAutoVerif";
			this->checkBoxAutoVerif->Size = System::Drawing::Size(55, 17);
			this->checkBoxAutoVerif->TabIndex = 17;
			this->checkBoxAutoVerif->Text = L"AutoV";
			this->checkBoxAutoVerif->UseVisualStyleBackColor = true;
			this->checkBoxAutoVerif->Visible = false;
			this->checkBoxAutoVerif->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxAuto_CheckedChanged);
			// 
			// buttonAuto
			// 
			this->buttonAuto->Location = System::Drawing::Point(34, 58);
			this->buttonAuto->Name = L"buttonAuto";
			this->buttonAuto->Size = System::Drawing::Size(20, 20);
			this->buttonAuto->TabIndex = 18;
			this->buttonAuto->Text = L"A";
			this->buttonAuto->UseVisualStyleBackColor = true;
			this->buttonAuto->Visible = false;
			this->buttonAuto->Click += gcnew System::EventHandler(this, &MyForm::buttonAuto_Click);
			// 
			// shapeContainer1
			// 
			this->shapeContainer1->Location = System::Drawing::Point(0, 0);
			this->shapeContainer1->Margin = System::Windows::Forms::Padding(0);
			this->shapeContainer1->Name = L"shapeContainer1";
			this->shapeContainer1->Shapes->AddRange(gcnew cli::array< Microsoft::VisualBasic::PowerPacks::Shape^  >(1) {this->rectangleShape1});
			this->shapeContainer1->Size = System::Drawing::Size(284, 261);
			this->shapeContainer1->TabIndex = 19;
			this->shapeContainer1->TabStop = false;
			// 
			// rectangleShape1
			// 
			this->rectangleShape1->Location = System::Drawing::Point(70, 42);
			this->rectangleShape1->Name = L"rectangleShape1";
			this->rectangleShape1->Size = System::Drawing::Size(148, 204);
			// 
			// checkBoxAutoSend
			// 
			this->checkBoxAutoSend->AutoSize = true;
			this->checkBoxAutoSend->Location = System::Drawing::Point(112, 213);
			this->checkBoxAutoSend->Name = L"checkBoxAutoSend";
			this->checkBoxAutoSend->Size = System::Drawing::Size(55, 17);
			this->checkBoxAutoSend->TabIndex = 20;
			this->checkBoxAutoSend->Text = L"AutoS";
			this->checkBoxAutoSend->UseVisualStyleBackColor = true;
			this->checkBoxAutoSend->Visible = false;
			this->checkBoxAutoSend->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBoxAutoSend_CheckedChanged);
			// 
			// textBoxAutoS
			// 
			this->textBoxAutoS->Location = System::Drawing::Point(122, 231);
			this->textBoxAutoS->Name = L"textBoxAutoS";
			this->textBoxAutoS->Size = System::Drawing::Size(55, 20);
			this->textBoxAutoS->TabIndex = 21;
			this->textBoxAutoS->Text = L"500";
			this->textBoxAutoS->Visible = false;
			// 
			// timer2
			// 
			this->timer2->Interval = 333;
			this->timer2->Tick += gcnew System::EventHandler(this, &MyForm::timer2_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->textBoxAutoS);
			this->Controls->Add(this->checkBoxAutoSend);
			this->Controls->Add(this->buttonAuto);
			this->Controls->Add(this->checkBoxAutoVerif);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->labelCharUnsignedConnection);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->checkBoxCode);
			this->Controls->Add(this->buttonSend);
			this->Controls->Add(this->labelConnectionType);
			this->Controls->Add(this->checkBoxDraw);
			this->Controls->Add(this->buttonRedireccionar);
			this->Controls->Add(this->radioButtonNormal);
			this->Controls->Add(this->radioButtonESE_GRS);
			this->Controls->Add(this->labelError);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->shapeContainer1);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(300, 300);
			this->MinimumSize = System::Drawing::Size(300, 300);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(comboBox1->Text!="SERIAL___PORT"&&comboBox1->Text!="TCP_IP_SERVER"&&comboBox1->Text!="TCP_IP_CLIENT")
			 {
				 textBox1->Enabled=false;
				 textBox2->Enabled=false;
				 button1->Enabled=false;
				 return;
			 }
			 textBox1->Enabled=true;
			 textBox2->Enabled=true;
			 button1->Enabled=true;
			 if(comboBox1->Text=="SERIAL___PORT")
			 {
				 c->SetType(ConnectionType::SERIAL_PORT,c);
				 textBox1->Text="COM1";
				 textBox2->Text="9600";
			 }
			 else if(comboBox1->Text=="TCP_IP_SERVER")
			 {
				 c->SetType(ConnectionType::TCP_IP_SERVER,c);
				 textBox1->Text="127.0.0.1";
				 textBox2->Text="55555";
			 }
			 else if(comboBox1->Text=="TCP_IP_CLIENT")
			 {
				 c->SetType(ConnectionType::TCP_IP_CLIENT,c);
				 textBox1->Text="127.0.0.1";
				 textBox2->Text="55555";
			 }

		 }
private: System::Void OnTExtChanged(System::Object^  sender, System::EventArgs^  e) {
			if(comboBox1->Text!="SERIAL___PORT"&&comboBox1->Text!="TCP_IP_SERVER"&&comboBox1->Text!="TCP_IP_CLIENT")
			 {
				 textBox1->Enabled=false;
				 textBox2->Enabled=false;
				 button1->Enabled=false;
				 return;
			 }
			
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(Interfaz==0)
			 {
				 Interfaz=1;
			    const char*txb1=context.marshal_as<const char*>(textBox1->Text);
			    const char*txb2=context.marshal_as<const char*>(textBox2->Text);
			    if(c->GetType()==ConnectionType::SERIAL_PORT)
			       c=new PuertoSerie();
		        else if(c->GetType()==ConnectionType::TCP_IP_CLIENT)
			      c=new TcP_ip_Client();
		        else if(c->GetType()==ConnectionType::TCP_IP_SERVER)
			       c=new TcP_ip_Server();

			    if(!c->inicializa(txb1,atol(txb2)))
			    {
				    labelError->Text=gcnew String(c->ErrorStr());
				    System::Windows::Forms::MessageBox::Show(labelError->Text);
				    labelError->Visible=true;
					Interfaz=0;
				    return;
			    }
			    Interfaz05();
			}
			 else if(Interfaz==1)
			 {
				 if(SendCont)
				 {
					 InterfazAutoSend(false);
				 }
				 Interfaz=0;
				 Interfaz0();
				 c->CloseConnection();
				 

			 }
			     
		 }
public:
	void Interfaz0()
	{
		labelError->Visible=false;
		labelConnectionType->Visible=false;
		labelCharUnsignedConnection->Visible=false;
		radioButtonESE_GRS->Visible=false;
		radioButtonNormal->Visible=false;
		buttonRedireccionar->Visible=false;
		button2->Visible=false;
		checkBoxDraw->Visible=false;
		checkBoxCode->Visible=false;
		buttonSend->Visible=false;
		panel1->Visible=false;
		checkBoxAutoVerif->Visible=false;
		checkBoxAutoSend->Visible=false;
		buttonAuto->Visible=false;
		textBoxAutoS->Visible=false;
		textBox2->Location = System::Drawing::Point(97,145);
		textBox1->Location = System::Drawing::Point(97,103);
		button1->Location= System::Drawing::Point(90,213);
		button1->Text="Connect";
		button1->Size = System::Drawing::Size(110,23);
		comboBox1->Visible=true;
		textBox1->Visible=true;
		textBox2->Visible=true;
		rectangleShape1->Visible=true;
		textBox1->Text=gcnew String(c->getChar());
		textBox2->Text=Convert::ToString(c->getunsigned());
	}
	void Interfaz05()
	{
		labelConnectionType->Location=Point(61,4);
		rectangleShape1->Visible=false;
		if(c->GetType()==ConnectionType::TCP_IP_SERVER)
		{
			 comboBox1->Visible=false;
			 textBox1->Visible=false;
			 textBox2->Visible=false;
	         button1->Text="Disconnect";
			 button1->Location = System::Drawing::Point(205,226);
			 button1->Size = System::Drawing::Size(71, 23);
			 labelConnectionType->Visible=true;
			 labelConnectionType->Text=comboBox1->Text;
			 button2->Visible=true;
		}
		else
			Interfaz1();

	}
	void Interfaz1()
		 {
			 cont=0;
			 labelError->Visible=false;
			 buttonSend->Visible=true;
			 button1->Text="Disconnect";
			 button1->Location = System::Drawing::Point(205,226);
			 button1->Size = System::Drawing::Size(71, 23);
			 comboBox1->Visible=false;
			 checkBoxAutoSend->Checked=false;
			 textBoxAutoS->Visible=false;
			 labelConnectionType->Visible=true;
			 labelConnectionType->Text=comboBox1->Text;
			 radioButtonNormal->Location = System::Drawing::Point(102,70);
			 radioButtonESE_GRS->Location = System::Drawing::Point(102,47);
			 textBox1->Visible=true;
			 textBox2->Visible=true;
			 radioButtonESE_GRS->Visible=true;
			 radioButtonNormal->Visible=true;
			 ActivateDesactiveRadButt0(true);
			 labelCharUnsignedConnection->Text=gcnew String(c->getChar())+"::"+Convert::ToString(c->getunsigned());
			 labelCharUnsignedConnection->Visible=true;
			 checkBoxAutoVerif->Visible=true;
			 checkBoxAutoSend->Visible=true;
		 }
	void  ActivateDesactiveRadButt0(bool ActiveDesact)
	{
	 if(ActiveDesact)
		{
	     buttonRedireccionar->Visible=true;
	     checkBoxDraw->Visible=true;
		 checkBoxCode->Visible=true;
		  textBox2->Visible=true;
		 textBox1->Text="00000001";
		 textBox2->Text="00000001"; 
		 textBox1->Location = System::Drawing::Point(97,110);
         textBox2->Location = System::Drawing::Point(97,136);
		 this->textBox1->MaxLength = 8;
		 this->textBox2->MaxLength = 8;
		}
	 else
	 {
	    buttonRedireccionar->Visible=false;
	    checkBoxDraw->Visible=false;
		checkBoxCode->Visible=false;
	 }
}
	void  ActivateDesactiveRadButt1(bool ActiveDesact)
	{
	 if(ActiveDesact)
  	 {
		 textBox1->Location = System::Drawing::Point(97,103);
		 textBox2->Location = System::Drawing::Point(97,145);
		 textBox1->Text="DataToSend";
		 textBox2->Visible=false;
	 }
	}
	char*ToBinary(const char*HigthByte,const char*LowByte)
	{
		if(strlen(HigthByte)!=8||strlen(LowByte)!=8)
		{
			System::Windows::Forms::MessageBox::Show("Error:Must be 8 characters by Byte");
			return NULL;
		}
		bool errHigth0=true,errLow0=true;
		for(unsigned i=0;i<8;i++)
		{
			if((HigthByte[i]!='1'&&HigthByte[i]!='0')||(LowByte[i]!='1'&&LowByte[i]!='0'))
			{
			    System::Windows::Forms::MessageBox::Show("Error:Must be all characters 0 or 1");
				return NULL;
			}
			if(HigthByte[i]=='1'&&errHigth0)
				errHigth0=false;
			if(LowByte[i]=='1'&&errLow0)
				errLow0=false;
		}
		if(errHigth0||errLow0)
		{
			System::Windows::Forms::MessageBox::Show("Error:At least one character must be 1");
			return NULL;
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
	void SendAuto(){
	
		cont++;
		if(cont==10)
		{
			cont=0;
			buttonAuto_Click(gcnew System::Object,gcnew System::EventArgs);
		}
	};
	void InterfazAutoSend(bool activDesact)
	{
		if(activDesact)
		{
			 const char*txbAS=context.marshal_as<const char*>(textBoxAutoS->Text);
			for(unsigned i=0;i<strlen(txbAS);i++)	 
			{
				if(!isalnum(txbAS[i]))
				{
					System::Windows::Forms::MessageBox::Show("Characters of Interval not valid");
					textBoxAutoS->Focus();
					return;
				}
			}
			SendCont=true;
			buttonSend->Text="Stop";
			textBox1->Enabled=false;
			textBox2->Enabled=false;
			checkBoxAutoSend->Enabled=false;
			checkBoxDraw->Enabled=false;
			checkBoxAutoVerif->Enabled=false;
			checkBoxCode->Enabled=false;
			radioButton3->Enabled=false;
			radioButton4->Enabled=false;
			radioButtonESE_GRS->Enabled=false;
			radioButtonNormal->Enabled=false;
			panel1->Enabled=false;
			textBoxAutoS->Enabled=false;
			buttonRedireccionar->Enabled=false;
			timer2->Interval = (int)atoi(txbAS);
			timer2->Enabled=true;
		}
		else
		{
			SendCont=false;
			timer2->Enabled=false;
			buttonSend->Text="AutoSend";
			textBox1->Enabled=true;
			textBox2->Enabled=true;
			checkBoxAutoSend->Enabled=true;
			checkBoxDraw->Enabled=true;
			checkBoxAutoVerif->Enabled=true;
			checkBoxCode->Enabled=true;
			radioButton3->Enabled=true;
			radioButton4->Enabled=true;
			radioButtonESE_GRS->Enabled=true;
			radioButtonNormal->Enabled=true;
			textBoxAutoS->Enabled=true;
			panel1->Enabled=true;
		    buttonRedireccionar->Enabled=true;	
		}
	}
	
private: System::Void radioButton1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(radioButtonESE_GRS->Checked)
			 {
				 ActivateDesactiveRadButt1(false);
				 ActivateDesactiveRadButt0(true);
				 checkBoxAutoVerif->Checked=true;
				 checkBoxAutoVerif->Visible=true;
				 buttonAuto->Visible=false;
				 checkBoxAutoSend->Visible=true;
				 checkBoxAutoSend->Checked=false;
				 textBoxAutoS->Visible=false;
			 }
			 else if(radioButtonNormal->Checked)
			 {
				 textBox1->Text="Send";
				 ActivateDesactiveRadButt1(true);
				 ActivateDesactiveRadButt0(false);
				 textBox1->Location = System::Drawing::Point(97,123);
				 checkBoxAutoVerif->Visible=false;
				 buttonAuto->Visible=false;
				 checkBoxAutoSend->Visible=false;
				 textBoxAutoS->Visible=false;
				 panel1->Visible=false;
			 }
		 }
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			const char*txb1=context.marshal_as<const char*>(textBox1->Text);
			char*a=new char[strlen(txb1)+1];
			a[strlen(txb1)]=0;
			for(unsigned i=0;i<strlen(txb1);i++)
			   a[i]=txb1[i];
			if(checkBoxDraw->Checked)
			{
			   a[6]='1';
			   textBox1->Text=gcnew String(a);
			}
			else 
			{
			   a[6]='0';
			   textBox1->Text=gcnew String(a);
			}
	}	 
private: System::Void checkBox2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			if(checkBoxCode->Checked)
			{
			   textBox1->Text="00000001";
			   textBox2->Text="00000011";
			   panel1->Visible=true;
			}
			else 
			{
			   textBox1->Text="00000001";
			   textBox2->Text="00000001";
			   panel1->Visible=false;
			}
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 char*s="00000001";
			 char*s1="00000111";
			 char*toSend=ToBinary(s,s1);
			 if(toSend!=NULL)
			 {
				 c->Trasmitir(toSend);
				 SendAuto();
			 }
		 }
private: System::Void buttonSend_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(checkBoxAutoSend->Checked==false)
			 {
			    const char*txb1=context.marshal_as<const char*>(textBox1->Text);
			    if(radioButtonESE_GRS->Checked)
			    {
				   const char*txb2=context.marshal_as<const char*>(textBox2->Text);
			       char*ToSend=ToBinary(txb1,txb2);
			       if(ToSend!=NULL)
			       {
				    c->Trasmitir(ToSend);
				     if(checkBoxAutoVerif->Checked)
					   SendAuto();
			       }
			    }
			    else if(radioButtonNormal->Checked)
			    {
				  c->Trasmitir((char*)txb1);
			    }
			 }
			 else
			 {
				 if(SendCont==false)
					 InterfazAutoSend(true);
				 else
					InterfazAutoSend(false);
			 }

		 }
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(Interfaz==1&&radioButtonESE_GRS->Checked)
			 {
				 if(textBox1->TextLength!=8)
					 buttonSend->Enabled=false; 
			     else
				 {
					 bool err0=true;;
					 for(unsigned i=0;i<8;i++)
					 {	 
						 if(textBox1->Text[i]=='1'&&err0)
							 err0=false;
						 if(textBox1->Text[i]!='1'&&textBox1->Text[i]!='0')
						 {
							  buttonSend->Enabled=false; 
							  return;
						 }
				     }
					 if(err0)
					 {
						 buttonSend->Enabled=false; 
						 return;
					 }


					 if(buttonSend->Enabled==false)
					    buttonSend->Enabled=true;
					 if(textBox1->Text[6]=='1')
					    checkBoxDraw->Checked=true;
				     else
			            checkBoxDraw->Checked=false;
				 }

				 
			 }
		 }
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(Interfaz==1&&radioButtonESE_GRS->Checked)
			 {
				 if(textBox2->TextLength!=8)
					 buttonSend->Enabled=false;
				 else 
				 {
					  bool err0=true;;
					 for(unsigned i=0;i<8;i++)
					 {	 
						 if(textBox2->Text[i]=='1'&&err0)
							 err0=false;
						 if(textBox2->Text[i]!='1'&&textBox2->Text[i]!='0')
						 {
							  buttonSend->Enabled=false; 
							  return;
						 }
				     }
					 if(err0)
					 {
						 buttonSend->Enabled=false; 
						 return;
					 }

					 if(buttonSend->Enabled==false)
					    buttonSend->Enabled=true;
					 if(textBox2->Text[6]=='1')
					    checkBoxCode->Checked=true;
				     else
			            checkBoxCode->Checked=false;
				 }

				 
			 }
		 }
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		     char*asd=c->PricipalAction();
			 if(c->Error())
			 {
				 labelError->Text=gcnew String(c->ErrorStr());
				 System::Windows::Forms::MessageBox::Show(labelError->Text);
			 }
			 else
			    Interfaz1();
			 timer1->Enabled=false;	 

		 }
private: System::Void button2_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 timer1->Enabled=true;
			 button2->Visible=false;
		 }
private: System::Void buttonAuto_Click(System::Object^  sender, System::EventArgs^  e) {
			 char*s="00000001";
			 char*s1="00000100";
			 char*toSend=ToBinary(s,s1);
			 if(toSend!=NULL)
				 c->Trasmitir(toSend);
		 }
private: System::Void checkBoxAuto_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(checkBoxAutoVerif->Checked) 
				 buttonAuto->Visible=false;
			 else
				 buttonAuto->Visible=true;
		 }
private: System::Void checkBoxAutoSend_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(checkBoxAutoSend->Checked)
			 {
				 textBoxAutoS->Visible=true;
				 buttonSend->Text="AutoSend";
			 }
			 else
			 {
				 textBoxAutoS->Visible=false;
				 buttonSend->Text="Send";
			 }
		 }
private: System::Void timer2_Tick(System::Object^  sender, System::EventArgs^  e) {
			 const char*txb1=context.marshal_as<const char*>(textBox1->Text);
			 const char*txb2=context.marshal_as<const char*>(textBox2->Text);
			 char*ToSend=ToBinary(txb1,txb2);
			 if(ToSend!=NULL)
			    {
				   c->Trasmitir(ToSend);
				   SendAuto();
			    }
		 }
private: System::Void radioButton3_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 const char*txb2=context.marshal_as<const char*>(textBox2->Text);
			 char*a=new char[strlen(txb2)+1];
			 a[strlen(txb2)]=0;
			   for(unsigned i=0;i<strlen(txb2);i++)
			      a[i]=txb2[i];
			   if(radioButton3->Checked)
			   {
			   a[0]='1';
			   textBox2->Text=gcnew String(a);
			   }
			   else
			   {
			   a[0]='0';
			   textBox2->Text=gcnew String(a);
			   }
		 }
};
}
