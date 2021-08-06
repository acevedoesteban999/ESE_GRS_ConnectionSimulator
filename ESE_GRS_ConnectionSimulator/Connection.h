#pragma once
#include <iostream>
#include <winsock.h>
#include <windows.h>
//#include<thread>
#include <string>
#include <ctime>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
enum ConnectionType
	{
		CONNECTION,SOCKET_SERVER,SOCKET_CLIENT,SERIAL_PORT
	};
enum TypeClient
	{
		Null,HTML,Windows,WEB,ESE_GRS
	};
class Connection
{
protected:
	ConnectionType t;
	bool IsConectado;
	bool error;
	char*errorstr,*message;
public:
	Connection(){
		t=ConnectionType::CONNECTION;
		IsConectado=error=false;
		errorstr=new char[1];
		errorstr[0]=0;
		message=new char[1];
		message[0]=0;
	};
	virtual ~Connection()
	{
		delete[]errorstr;
		delete[]message;
	};
	virtual void CloseConnection(){};
	virtual bool inicializa(const char*Ip, unsigned long Port){return false;};
	virtual char* Recibir()
	{
		/*if(EstaConectado())
		{
			 memset(buffer,0,sizeof(buffer));
			 int n=recv(t==ConnectionType::SOCKET_SERVER?cliente:server,buffer,sizeof(buffer),0);
			 if(n==0)
			 {
				 string s("Error 0 ");
				 errorstr=new char[s.length()+1];
				 for(unsigned i=0;i<s.length();i++)
					 errorstr[i]=s[i];
				 error=true;
				 return NULL;
			 }
			 if(n==-1)
			 {
					string s("C_Error 1 ");
					errorstr=new char[s.length()+1];
					for(unsigned i=0;i<s.length();i++)
						errorstr[i]=s[i];
					error=true;
					return NULL;
			 }
			 return buffer;
		}*/
		return NULL;
	 };
	virtual void Trasmitir( char*buffer,SOCKET s=NULL,bool ESEGRS=false){
		/*int n=send(t==ConnectionType::SOCKET_SERVER?cliente:server,buffer,strlen(buffer),0);
		 if(n==0)
		 {
		  string s("Error 0 ");
	      errorstr=new char[s.length()+1];
		  for(unsigned i=0;i<s.length();i++)
			 errorstr[i]=s[i];
		  error=true;
		  return;
		 }
		  if(n==-1)
		 {
			string s("Error 1 ");
			errorstr=new char[s.length()+1];
			for(unsigned i=0;i<s.length();i++)
				errorstr[i]=s[i];
		    error=true;
			return;
		 }*/
	 };
	virtual void Select(){}
	virtual char*getChar(){return nullptr;};
	virtual unsigned getunsigned(){return 0;};
	virtual void SocketServer_CerrarSocket(SOCKET s){};
	virtual char*SocketServer_List(){return "NULL";}
	virtual unsigned GetContClients(){return 0;};
	virtual bool StatusClient(){return false;};
	virtual void ActStatusClient(bool){};
	virtual char*SocketServer_ClienteList(unsigned i){return "NULL";} 
	virtual void SocketServer_CerrarSocketByIndex(unsigned i){};
	virtual void SetBoolCerrarSocket(bool b){};
	virtual bool SocketServer_ClientAcceso(unsigned i){return false;};
	virtual bool SocketServer_ClientIsUser(unsigned i){return false;};
	virtual unsigned SocketServer_ClientUserIndex(){return 10;};
	virtual void SocketServer_CambiarUser(unsigned i){};
	virtual bool SocketServer_ClientESE(unsigned i){return false;}
	virtual unsigned SocketServer_ClientESEIndex(){return 10;};
	virtual void SocketServer_SetESE(bool ESE){}
	bool Error(){return error;};
	bool EstaConectado(){return IsConectado;};
	char* ErrorStr(){return errorstr;};
	ConnectionType GetType(){return t;};
	static void SetType(ConnectionType CT,Connection*conn){conn->t=CT;};
	static char* GetMesage(Connection*conn){return conn->message;};
	
};
class Socket_Server:public Connection
{
class StackClients
	{
	class SocketCliente
		{
		public:
			SOCKET ID;
			SOCKADDR_IN Addr;
			time_t date;
			TypeClient t;
			SocketCliente()
			{
				t=TypeClient::Null;
			};
			~SocketCliente(){}
			void ActualizaDate()
			{
				date=time(0);
			}
		    operator SOCKET()
			{
				return ID;
			}

		};
	public:
		unsigned cont,cant;
		SocketCliente*clientes;
		unsigned user,userR,ESE;
		bool userNew,userRemov,ESEB;
		StackClients(int max=10)
		{
			this->cont=0;
			this->cant=max;
			clientes=new SocketCliente[max];
			user=userR=ESE=10;
			userNew=userRemov=ESEB=false;
		}
		~StackClients()
		{
			delete[]clientes;
		}
		void Add(SOCKET id,SOCKADDR_IN addr)
		{
			if(cont<cant)
			{
				clientes[cont].ID=id;
				clientes[cont].Addr=addr;
				clientes[cont++].ActualizaDate();
			}
		}
		bool Remove(SOCKET s)
		{
			if(cont>0)
			{
				for(unsigned i=0;i<cont;i++)
					if(clientes[i]==s)
					{
						return RemoveByIndex(i);
					}
			}
			return false;
		}
		bool RemoveByIndex(unsigned i)
		{
			if(cont>0&&i<cont)
			{
				closesocket(clientes[i]);	
				for(unsigned ii=i;ii<cont-1;ii++)
					clientes[ii]=clientes[ii+1];
				cont--;
				RemoveUser(i);
				if(i==ESE)
				{
					ESEB=false;
					ESE=10;
				}
				return true;
			}
			return false;
		}
		void ActuType(TypeClient t,SOCKET s)
		{
			for(unsigned i=0;i<cont;i++)
					if(clientes[i]==s)
					{
						ActuTypeByIndex(t,i);
					}
		}
		void ActuTypeByIndex(TypeClient t,unsigned i)
		{
			if(t==TypeClient::ESE_GRS)
			{
				if(!ESEB)
				{
					ESEB=true;
					ESE=i;
					this->clientes[i].t=t;
				}
				else
					this->clientes[i].t=TypeClient::Null;
			}
			else
			{
				this->clientes[i].t=t;
				if(user==10)
					ActualizaUser(i);
			}
		}
		SocketCliente GetSocketCliente(SOCKET s)
		{
			for(unsigned i=0;i<cont;i++)
				if(s==clientes[i])
					return clientes[i];
		}
		SocketCliente GetSocketClienteByIndex(unsigned i)
		{
				return clientes[i];
		}
		void ActualizaUser(unsigned i)
		{
			if(i<cont)
				if(clientes[i].t==TypeClient::WEB||clientes[i].t==TypeClient::Windows)
				{
					userNew=true;
					if(user!=10)
					{
						userRemov=true;
						userR=user;
					}
					user=i;
				}
		}
		void RemoveUser(unsigned i)
		{
			if(user==10)
				return;
			else if(i==user)
			{
				for(unsigned ii=0;ii<cont;ii++)
					if(clientes[ii].t==TypeClient::WEB||clientes[ii].t==TypeClient::Windows)
					{
						userR=user;
						user=ii;
						userNew=userRemov=true;
						return;
					}
			user=10;
			}
			else if(user>i)
				user--;
		}
	};
private:
	
	WSADATA wsData;
	SOCKET server;
	SOCKADDR_IN serveraddr,clientaddr;
	fd_set descriptoresLectura;
	StackClients ManejadorClientes;	
	char*ip,*buffer;
	struct timeval tv;
	unsigned Port;
	bool LoopThread;
	bool ClientsStatus;
	bool CerrandoSoket;
public:
	void Select()
	{
		LoopThread=true;
		cout<<"Esperando clientes"<<endl;
		while(LoopThread)
		{
			FD_ZERO(&descriptoresLectura);
			FD_SET(server,&descriptoresLectura);
			for (unsigned i=0; i<ManejadorClientes.cont; i++)
				FD_SET(ManejadorClientes.clientes[i],&descriptoresLectura);
			select(server,&descriptoresLectura,NULL,NULL,NULL);
			if(!LoopThread)
				return;
			if(CerrandoSoket)
				continue;
			if(FD_ISSET(server,&descriptoresLectura))
			{
				SOCKET client;
				int clientaddrSize=sizeof(clientaddr);
				if((client=accept(server,(SOCKADDR*)&clientaddr,&clientaddrSize))<0)
				{
				   cout<<"Cuidado!!,Error al conectarse un cliente"<<endl;
				}
				else
				{
					if(ManejadorClientes.cont==ManejadorClientes.cant)
					{
						closesocket(client);
						continue;
					}
					cout<<"++++++++++++++++++"<<"Cliente Conectado:";
					ManejadorClientes.Add(client,clientaddr);
					cout<<client<<"-ip:"<<inet_ntoa(ManejadorClientes.clientes[ManejadorClientes.cont-1].Addr.sin_addr)<<"++++++++++++++++++"<<endl;
					ActStatusClient(true);					
				}
			}
			else
			{
				for(unsigned i=0;i<ManejadorClientes.cont;i++)
				{
					if(!FD_ISSET(ManejadorClientes.clientes[i],&descriptoresLectura))
						continue;
					memset(buffer,0,sizeof(buffer));
					int n=recv(ManejadorClientes.clientes[i],buffer,1024,0);
					switch(n)
					{
					case -1:
						cout<<"Error al leer al cliente, ";
					case 0:
						SocketServer_CerrarSocketByIndex(i);
						break;
					default:
						buffer[(unsigned)n]=0;
						cout<<"////////////////////Resivido de "<<ManejadorClientes.clientes[i]<<"///////////////////"<<endl<<buffer<<"//////////////////////////////////////////////////////////"<<endl;
						if(strlen(buffer)>=10)
						{
							char asd[11];
							asd[10]=0;
							for(unsigned j=0;j<10;j++)
								asd[j]=buffer[j];
							if(!strcmp(asd,"GET / HTTP"))
							{
								this->Trasmitir(RespuestaClienteHTML(),ManejadorClientes.clientes[i]);
								this->ManejadorClientes.ActuTypeByIndex(TypeClient::HTML,i);
							}
							else if(!strcmp(asd,"ESEGRS ESE"))
							{
								this->ManejadorClientes.ActuTypeByIndex(TypeClient::ESE_GRS,i);
								if(ManejadorClientes.ESE==i)
									Trasmitir("ESE_GRS ESE_GRS",ManejadorClientes.clientes[i]);
							}
							else if(!strcmp(asd,"ESEGRS WIN"))
							{
								this->ManejadorClientes.ActuTypeByIndex(TypeClient::Windows,i);
								if(ManejadorClientes.userNew&&ManejadorClientes.user==i)
								{
									Trasmitir("ESE_GRS USER",ManejadorClientes.clientes[i]);
									ManejadorClientes.userNew=false;
								}
							}
							else if(!strcmp(asd,"ESEGRS WEB"))
							{
								this->ManejadorClientes.ActuTypeByIndex(TypeClient::WEB,i);
								if(ManejadorClientes.userNew&&ManejadorClientes.user==i)
								{
									Trasmitir("ESE_GRS USER",ManejadorClientes.clientes[i]);
									ManejadorClientes.userNew=false;
								}
							}
						}
						if(SocketServer_ClientIsUser(i))
							Trasmitir(buffer);
						else if(SocketServer_ClientESE(i))
							Trasmitir(buffer,NULL,true);
						break;
					}
				}
			}
			
		}
	}
	char*RespuestaClienteHTML()
	{
		return "HTTP/1.1 200 OK\r\n"
			"Content-Type text/html\r\n"
			"\r\n"
			"<!DOCTYPE html>"
			"<html lang=\"en\">"
			"<head>"
			"<meta charset=\"UTF-8\">"
			"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
			"<title>ESE_GRS SERVER</title>"
			"</head>"
			"<body>"
				"<div style=\"text-align: center;\">"
				"<h1 >ESE_GRS Server</h1>"
				"<h3 style=\"font-family: Georgia, 'Times New Roman', Times, serif;\">"
				"Aqui se encuentra alojado el servidor en C++ a partir de Sockets."
				"Para empezar a  utilizar  nuestros servicios descargue la "
				"<a href=\"https://github.com/Esteban191900/ESE_GRS-Class\" target=\"_blank\">App" 
				"para windows</a>, o desde el <a href=\"https://esteban191900.github.io/ESE_GRS_WEBGL_THREEJS/\" target=\"_blank\">"
				"simulador online</a>"
            "</h3>"
			"</body>"
			"</html>";
	}
	Socket_Server():Connection()
	{
		this->t=ConnectionType::SOCKET_SERVER;
		ip=new char[1];
		buffer=new char[1024];
		LoopThread=false;
		ClientsStatus=false;
		CerrandoSoket=false;
		tv.tv_sec=0;
		tv.tv_usec=500000;
		
	}
	~Socket_Server()
	{
		  delete[]ip;
		  delete[]buffer;
		  this->CloseConnection();
	};
	void CloseConnection(){
		if(this->EstaConectado())
		{
			LoopThread=false;
			for(unsigned i=0;i<ManejadorClientes.cont;i++)
				closesocket(ManejadorClientes.clientes[i]);
			WSACleanup();
			//th->join();
			IsConectado=false;
		}
	} 
	bool inicializa(const char* Ip, unsigned long Port)
	 {
		WSAStartup(MAKEWORD(2,0),&wsData);
		if((server=socket(AF_INET,SOCK_STREAM,0))<0)
		{
			this->error=true;
			string s("Error 1 ,Socket no creado");
			delete[]errorstr;
			errorstr=new char[s.length()+1];
			errorstr[s.length()]=0;
			for(unsigned i=0;i<s.length();i++)
				 errorstr[i]=s[i];
			cout<<errorstr<<endl;
			return false;
		}
		serveraddr.sin_addr.s_addr=inet_addr((const char*)Ip);   //INADDR_ANY;
		serveraddr.sin_family=AF_INET;
		serveraddr.sin_port=htons((u_short)Port);
		if(::bind(server,(SOCKADDR*)&serveraddr,sizeof(serveraddr))!=0)
		{
			this->error=true;
			string s("Error 2 , bind no iniciado");
			delete[]errorstr;
			errorstr=new char[s.length()+1];
			errorstr[s.length()]=0;
			for(unsigned i=0;i<s.length();i++)
				 errorstr[i]=s[i];
			cout<<errorstr<<endl;
			return false;
	   }
		if(listen(server,0)!=0)
		{
			this->error=true;
			string s("Error 3 , listen no iniciado");
			delete[]errorstr;
			errorstr=new char[s.length()+1];
			errorstr[s.length()]=0;
			for(unsigned i=0;i<s.length();i++)
				 errorstr[i]=s[i];
			cout<<errorstr<<endl;
			return false;
		}

		error=false;
		IsConectado=true;
		delete[]ip;
		this->ip=new char[strlen(Ip)+1];
	    this->ip[strlen(Ip)]=0;
	    for(unsigned i=0;i<strlen(Ip);i++)
	   	   this->ip[i]=Ip[i];
		this->Port=Port;
		cout<<"Server incicado en "<<ip<<":"<<Port<<endl;
		//th=new thread(&Socket_Server::Select,this);
		return true;
	 
	 }
	void Trasmitir(char*buffer,SOCKET s=NULL,bool ESEGRS=false){
		int n=-2;
		if(s!=NULL)
		{
				n=send(s,buffer,strlen(buffer),0);
		}
		else
		{
			for(unsigned i=0;i<ManejadorClientes.cont;i++)
				if(!ESEGRS)
				{
					if(i!=ManejadorClientes.user&&(ManejadorClientes.clientes[i].t==TypeClient::WEB||ManejadorClientes.clientes[i].t==TypeClient::Windows))
						Trasmitir(buffer,ManejadorClientes.clientes[i]);
				}
				else
					if(ManejadorClientes.clientes[i].t==TypeClient::WEB||ManejadorClientes.clientes[i].t==TypeClient::Windows)
						Trasmitir(buffer,ManejadorClientes.clientes[i]);
		}
		 if(n==0)
		 {
				cout<<"Error 0 , no se ha podido transmitir, cliente:"<<s<<" desconectado"<<endl;
				return;
		  }
		  if(n==-1)
		  {
				cout<<"Error 1, cliente:"<<s<<" desconectado"<<endl;
				return;
		  }
	 };
	char*getChar(){return ip;};
	unsigned getunsigned(){return Port;};
	void SocketServer_CerrarSocket(SOCKET s)
	{
		if(ManejadorClientes.Remove(s))
		{
				cout<<endl<<"-------------------Cliente desconectado:"<<s<<"------------------"<<endl;		
				closesocket(s);
				if(ManejadorClientes.userNew)
				{
					Trasmitir("ESE_GRS USER",ManejadorClientes.clientes[ManejadorClientes.user]);
					ManejadorClientes.userNew=false;
				}
				ActStatusClient(true);
		}
	}
	void SocketServer_CerrarSocketByIndex(unsigned i)
	{
		if(ManejadorClientes.RemoveByIndex(i))
		{
			cout<<endl<<"-------------------Cliente desconectado:"<<ManejadorClientes.clientes[i]<<"------------------"<<endl;		
			if(CerrandoSoket)
				CerrandoSoket=false;
			if(ManejadorClientes.userNew)
			{
				Trasmitir("ESE_GRS USER",ManejadorClientes.clientes[ManejadorClientes.user]);
				ManejadorClientes.userNew=false;
			}
			ActStatusClient(true);
		}
		
	}
	char*SocketServer_List()
	{
		if(!ManejadorClientes.cont)
		{
			string s("Lista vacia");
			char*ListaVacia=new char[s.length()+1];
			ListaVacia[s.length()]=0;
			for(unsigned i=0;i<s.length();i++)
				ListaVacia[i]=s[i];
			return ListaVacia;
		}
		string s;
		for(unsigned i=0;i<ManejadorClientes.cont;i++)
		{
		s+="_Id:";
		s+=to_string(ManejadorClientes.clientes[i]);
		s+="\n_Tipo:";
		s+=(ManejadorClientes.clientes[i].t==TypeClient::HTML?"HTML":ManejadorClientes.clientes[i].t==TypeClient::Windows?"WIND":ManejadorClientes.clientes[i].t==TypeClient::WEB?"WEB":ManejadorClientes.clientes[i].t==TypeClient::ESE_GRS?"ESE":"NULL");
		s+="\n_Acceso:";
		s+=(ManejadorClientes.user==i||ManejadorClientes.ESE==i)?"TRUE":"FALSE";
		s+="\n_Ip:";
		s+=inet_ntoa(ManejadorClientes.clientes[i].Addr.sin_addr);
		s+="\n_Fecha:";
		s+=ctime(&ManejadorClientes.clientes[i].date);
		s+="\n\n";
		}
		char*toReturn=new char[s.length()+1];
		toReturn[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			toReturn[i]=s[i];
		return toReturn;

	}
	char*SocketServer_ClienteList(unsigned i)
	{
		if(ManejadorClientes.cont<=i)
		{
			string s("Lista vacia");
			char*ListaVacia=new char[s.length()+1];
			ListaVacia[s.length()]=0;
			for(unsigned i=0;i<s.length();i++)
				ListaVacia[i]=s[i];
			return ListaVacia;
		}
		string s;
		s+="_Id:";
		s+=to_string(ManejadorClientes.clientes[i]);
		s+="\n_Tipo:";
		s+=(ManejadorClientes.clientes[i].t==TypeClient::HTML?"HTML":ManejadorClientes.clientes[i].t==TypeClient::Windows?"WIND":ManejadorClientes.clientes[i].t==TypeClient::WEB?"WEB":ManejadorClientes.clientes[i].t==TypeClient::ESE_GRS?"ESE":"NULL");
		s+="\n_Acceso:";
		s+=(ManejadorClientes.user==i||ManejadorClientes.ESE==i)?"TRUE":"FALSE";
		s+="\n_Ip:";
		s+=inet_ntoa(ManejadorClientes.clientes[i].Addr.sin_addr);
		s+="\n_Fecha:";
		s+=ctime(&ManejadorClientes.clientes[i].date);	
		
		char*toReturn=new char[s.length()+1];
		toReturn[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			toReturn[i]=s[i];
		return toReturn;
	}
	bool SocketServer_ClientAcceso(unsigned i)
	{
		if(ManejadorClientes.cont<=i)
		 return false;
		if(ManejadorClientes.clientes[i].t==TypeClient::WEB||ManejadorClientes.clientes[i].t==TypeClient::Windows)
			return true;
		return false;
	}
	bool SocketServer_ClientIsUser(unsigned i)
	{
		if(ManejadorClientes.cont<=i)
			return false;
		if(ManejadorClientes.user==i)
			return true;
		return false;
	}
	unsigned GetContClients(){return ManejadorClientes.cont;};
	unsigned SocketServer_ClientUserIndex()
	{
		return ManejadorClientes.user;
	};
	unsigned SocketServer_ClientESEIndex(){
		return ManejadorClientes.ESE;
	};
	bool SocketServer_ClientESE(unsigned i)
	{
		if(ManejadorClientes.cont<=i)
			return false;
		if(ManejadorClientes.ESE==i)
			return true;
		return false;
	}
	void SocketServer_CambiarUser(unsigned i)
	{
		ManejadorClientes.ActualizaUser(i);
		if(ManejadorClientes.userNew)
		{
			Trasmitir("ESE_GRS USER",ManejadorClientes.clientes[ManejadorClientes.user]);
			ManejadorClientes.userNew=false;
			if(ManejadorClientes.userRemov)
			{
				Trasmitir("ESE_GRS !USER",ManejadorClientes.clientes[ManejadorClientes.userR]);
				ManejadorClientes.userRemov=false;
			}
		}
		ActStatusClient(true);
	}
	bool StatusClient()
	{
		return ClientsStatus;
	};
	void SetBoolCerrarSocket(bool b)
	{
		CerrandoSoket=b;
	};
	void ActStatusClient(bool CLST)
	{
		ClientsStatus=CLST;
	};
	void SocketServer_SetESE(bool ESE)
	{
		if(ESE)
			ManejadorClientes.ESE=10;
		ManejadorClientes.ESEB=ESE;
	}
	/*char* ActionAfterError()
	{
		if(error=true)
		{
		   return ConnectClient();
		}
		return "No habia un error";
	};*/
	/*char* ConnectClient()
	{
		int clientaddrSize=sizeof(clientaddr);
		   if((cliente=accept(server,(SOCKADDR*)&clientaddr,&clientaddrSize))<0)
		   {
			  this->error=true;
			  this->errorstr="Error al conectar un cliente";
			  return this->errorstr;
		   }
		   this->message="Cliente Conectado";
		   error=false;
		   return this->message;
	}*/
};
class Socket_Client:public Connection
{
private:
	WSADATA wsData;
	SOCKET server;
	SOCKADDR_IN serveraddr,clientaddr;
	char*ip,*buffer;
	unsigned Port;
public:
	Socket_Client():Connection()
	{
		this->t=ConnectionType::SOCKET_CLIENT;
		ip=new char[1];
		buffer=new char[1024];
	}
	~Socket_Client(){
		delete[]ip;
		delete[]buffer;
		this->CloseConnection();
	};
	void CloseConnection(){
		if(EstaConectado())
		{
			closesocket(server);
			WSACleanup();
			IsConectado=false;
		}
	}
	bool inicializa(const char* Ip, unsigned long Port)
	{
	    WSAStartup(MAKEWORD(2,0),&wsData);
		if((server=socket(AF_INET,SOCK_STREAM,0))<0)
		{
			this->error=true;
			string s("Error 0 ,socket no creado");
			delete[]errorstr;
			errorstr=new char[s.length()+1];
			errorstr[s.length()]=0;
			for(unsigned i=0;i<s.length();i++)
				 errorstr[i]=s[i];
			cout<<errorstr<<endl;
			return false;
		}
		serveraddr.sin_addr.s_addr=inet_addr((const char*)Ip);
		serveraddr.sin_family=AF_INET;
		serveraddr.sin_port=htons((u_short)Port);
		if(connect(server,(SOCKADDR*)&serveraddr,sizeof(serveraddr))<0)
		 {
			string s("Error 1 : no se puedo conectar con:"+string(Ip)+":"+to_string(Port));
			delete[]errorstr;
			errorstr=new char[s.length()+1];
			errorstr[s.length()]=0;
			for(unsigned i=0;i<s.length();i++)
				 errorstr[i]=s[i];
			this->error=true;
			cout<<errorstr<<endl;
			return false;
		 }
		else
		{
		
		string s(string(Ip)+":"+to_string(Port));
		delete[]errorstr;
		errorstr=new char[s.length()+1];
		errorstr[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
		    errorstr[i]=s[i];
		}


		error=false;
		IsConectado=true;
		delete[]ip;
		this->ip=new char[strlen(Ip)+1];
	    this->ip[strlen(Ip)]=0;
	    for(unsigned i=0;i<strlen(Ip);i++)
	   	   this->ip[i]=Ip[i];
		this->Port=Port;

		return true;
	};
	char* Recibir()
	{
		if(EstaConectado())
		{
			 memset(buffer,0,sizeof(buffer));
			 int n=recv(server,buffer,255,0);
			 if(n==0)
			 {
				 string s("Error 0, dato no recivido, conexion cerrada");
				 delete[]errorstr;
				 errorstr=new char[s.length()+1];
				 errorstr[s.length()]=0;
				 for(unsigned i=0;i<s.length();i++)
					 errorstr[i]=s[i];
				 error=true;
				 cout<<errorstr<<endl;
				 CloseConnection();
				 return NULL;
			 }
			 if(n==-1)
			 {
					string s("Error 1, Conexion perdida");
					delete[]errorstr;
					errorstr=new char[s.length()+1];
					errorstr[s.length()]=0;
					for(unsigned i=0;i<s.length();i++)
						errorstr[i]=s[i];
					error=true;
					cout<<errorstr<<endl;
					CloseConnection();
					return NULL;
			 }
			 else if(n>0)
			 {
				buffer[n]=0;
				return buffer;
			 }
		}
		return NULL;
	 };
	void Trasmitir( char*buffer,SOCKET s,bool ESEGRS=false){
		if(EstaConectado())
		{
			 int n=send(server,buffer,strlen(buffer),0);
			 if(n==0)
			 {
			  string s("Error 0 , dato no enviado, conexion cerrada");
			  delete[]errorstr;
			  errorstr=new char[s.length()+1];
			  for(unsigned i=0;i<s.length();i++)
				 errorstr[i]=s[i];
			  cout<<errorstr<<endl;
			  error=true;
			  CloseConnection();
			  return;
			 }
			  if(n==-1)
			 {
				string s("Error 1, Conexion Perdida");
				delete[]errorstr;
				errorstr=new char[s.length()+1];
				for(unsigned i=0;i<s.length();i++)
					errorstr[i]=s[i];
				error=true;
				cout<<errorstr<<endl;
				CloseConnection();
				return;
			 }
		}
	 };
	char*getChar(){return ip;};
	unsigned getunsigned(){return Port;};
};
class PuertoSerie:public Connection
{
	
private:
	HANDLE handler;
	char*Puerto;
	unsigned long Speed;
public:
	PuertoSerie():Connection()
	{
		Puerto=new char[1];
		this->t=ConnectionType::SERIAL_PORT;
	};
	//PuertoSerie(System::String^PuertoCom, unsigned long Velocidad);
	~PuertoSerie()
    {
		delete[]Puerto;
		CloseConnection();
    }
	void CloseConnection()
	{
		if(IsConectado)
		{
		   IsConectado=false;
		   CloseHandle(handler);
	    }
	
	}
	bool inicializa(const char* PuertoCom, unsigned long Velocidad)
{
	handler=CreateFile(PuertoCom,GENERIC_READ | GENERIC_WRITE,NULL,NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);
	if (handler==INVALID_HANDLE_VALUE)
	{
		string s("C_Error 0 :"+string(PuertoCom)+":"+to_string(Velocidad));
		delete[]errorstr;
		errorstr=new char[s.length()+1];
		errorstr[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			 errorstr[i]=s[i];
		error=true;
		return false;
	}
	DCB ParametrosTxSerie;
	if (!GetCommState(handler,&ParametrosTxSerie))
	{
		string s("Error 1 :"+string(PuertoCom)+":"+to_string(Velocidad));
		delete[]errorstr;
		errorstr=new char[s.length()+1];
		errorstr[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			errorstr[i]=s[i];
		error=true;
		return false;
	}
	ParametrosTxSerie.DCBlength=sizeof(DCB);
	ParametrosTxSerie.BaudRate=Velocidad;
	ParametrosTxSerie.ByteSize=8;
	ParametrosTxSerie.StopBits=TWOSTOPBITS;
	ParametrosTxSerie.Parity=(BYTE)PARITY_NONE;
	if(!SetCommState(handler,&ParametrosTxSerie))
	{
		string s("Error 2 :"+string(PuertoCom)+":"+to_string(Velocidad));
		delete[]errorstr;
		errorstr=new char[s.length()+1];
		errorstr[s.length()]=0;
		for(unsigned i=0;i<s.length();i++)
			errorstr[i]=s[i];
		error=true;
		return false;
	}
	IsConectado=true;
	PurgeComm(handler,PURGE_RXCLEAR|PURGE_TXCLEAR);
	error=false;
	delete[]this->Puerto;
	this->Puerto=new char[strlen(PuertoCom)+1];
	this->Puerto[strlen(PuertoCom)]=0;
	for(unsigned i=0;i<strlen(PuertoCom);i++)
		this->Puerto[i]=PuertoCom[i];
	this->Speed=Velocidad;
	string s(string(PuertoCom)+":"+to_string(Velocidad));
	delete[]message;
	message=new char[s.length()+1];
	message[s.length()]=0;
	for(unsigned i=0;i<s.length();i++)
		message[i]=s[i];
	return true;
}
	char* Recibir()
	{
		char*cadena=NULL;
		if(EstaConectado())
		{
			DWORD leidos;
			COMSTAT cs;
			if(ClearCommError(handler,&leidos,&cs)==0)
			{
				this->error=true;
				string s("Error 0 ");
				delete[]errorstr;
				errorstr=new char[s.length()+1];
				errorstr[s.length()]=0;
				for(unsigned i=0;i<s.length();i++)
					 errorstr[i]=s[i];
				return cadena;
			}
			leidos=0;
			if(cs.cbInQue)
			{
				cadena=new char[cs.cbInQue+3];
				cadena[cs.cbInQue]=0;
				ReadFile(handler,cadena,cs.cbInQue,&leidos,NULL);
				return cadena;
			}
		}
		return cadena;
	};
	void Trasmitir(char *oBuffer,SOCKET s=NULL,bool ESEGRS=false)
	{
	DWORD iBytesWritten;
	iBytesWritten=0;
	WriteFile(handler,oBuffer,strlen(oBuffer),&iBytesWritten,NULL);
	}
	//void Trasmitir(System::String^data);
	char*getChar(){return Puerto;};
	unsigned getunsigned(){return Speed;};
};

