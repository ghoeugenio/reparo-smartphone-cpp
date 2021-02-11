#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

void fflush_stdin(){//limpar o buffer do teclado
	int ch;
	while((ch = getchar()) != '\n' && ch != EOF);
}

int numeroAleatorio(int max, int min){
	return rand()%(max - min + 1) + min;
}

typedef struct{
	bool end;
	bool finalizado;
	int custo;
	bool troca;
	bool pago;
	bool token;
}status;

typedef struct{
	string nome;
	string endereco;
	string modelo;
	bool garantia;
	char problema;
	string detalhes;
	int id;
	status s;
}dados;


int main(){
	
	int contador, laco, numAleatorio, auxint, i, x, j = 1;
	bool vef = false, vef2 = false, vef3 = false, vef4 = false, vef5 = false;
	dados registro[200];
	char v, menu, segundomenu, auxstr[20];
	float a, b, c, d, e, f, g, h;
	string sa = "Bateria ou impossibilidade do aparelho ser ligado", sh = "GPS";
	string sb = "Aparelho lento ou com travamentos", sc = "Cartao SIM inoperante";
	string sd = "Tela touchscreen", se = "Audio", sf = "Camera", sg = "Wireless";
	
	srand((unsigned)time(0));//para gerar o numero aleatorio
	
	while(1){
		system("cls");
		cout << "1)Fazer registro\n";
		cout << "2)Atualizar ordem de servico\n";
		cout << "3)Encerrar ordem de reparo\n";
		cout << "4)Registro de pagamento\n";
		cout << "5)Consulta de status\n";
		cout << "6)Relatorios\n";
		cout << "0)Fechar programa\n";
		cout << "Opcao: ";
		cin >> menu;
		fflush_stdin();
		
		if(menu == '0'){
			return 0;
		}
		
		if(menu == '1'){
			system("cls");
			cout << "Nome do cliente: ";
			getline(cin, registro[contador].nome);
			system("cls");
			cout << "Endereco do cliente: ";
			getline(cin, registro[contador].endereco);
			system("cls");			
			cout << "Modelo do aparelho: ";
			getline(cin, registro[contador].modelo);
			system("cls");
			cout << "Esta no periodo de garantia?(s ou n): ";
			cin >> v;
			laco = 1;
			while(laco){
				if (v == 's'){
					registro[contador].garantia = true;
					laco = 0;
				}
				else if (v == 'n'){
					registro[contador].garantia = false;
					laco = 0;
				}
				else{
					cout << "Erro, digite novamente: ";
					cin >> v;
				}
			}
			system("cls");
			cout << "a) " << sa <<"\n";
			cout << "b) " << sb <<"\n";
			cout << "c) " << sc <<"\n";
			cout << "d) " << sd <<"\n";
			cout << "e) " << se <<"\n";
			cout << "f) " << sf <<"\n";
			cout << "g) " << sg <<"\n";
			cout << "h) " << sh <<"\n";
			cout << "Categoria do problema: ";
			cin >> v;
			laco = 1;
			while(laco){
				if((v == 'a') || (v == 'b') || (v == 'c') || (v == 'd') || (v == 'e') || (v == 'f') || (v == 'g') || (v == 'h')){
					registro[contador].problema = v;
					break;
				}
				else{
					cout << "Erro, digite novamente: ";
					cin >> v;
				}
			}
			fflush_stdin();
			cout << "Detalhes do problema: ";
			getline(cin, registro[contador].detalhes);
			while(j){//garantir que nao haja pedidos com mesmo id
				j = 0;
				numAleatorio = numeroAleatorio(999,100);
				for(i = 0; i < contador; i++){
					if(numAleatorio == registro[i].id){
						j = 1;
					}
				}	
			}
			j = 1;	
			registro[contador].id = numAleatorio;
			contador++;
			cout << "Numero de identificacao: " << numAleatorio << "\n";
			system("pause");			
		}
		if (menu == '2'){
			system("cls");
			cout << "Numero de identificacao: ";
			cin >> auxstr;
			auxint = atoi(auxstr);
			vef2 = false;
			for(i = 0; i < contador; i++){	
				if((auxint == registro[i].id) && (!registro[i].s.end)){
					vef2 = true;
					if(registro[i].s.finalizado){
						cout << "Pedido ja finalizado\n";
						system("pause");
						break;
					}
					if(registro[i].s.end){
						cout << "Orcamento ja realizado\n";
						system("pause");
						break;
					}
					cout << "1)Reparar aparelho\n";
					cout << "2)Trocar aparelho\n";
					cin >> x;
					if(x == 2){
						registro[i].s.troca = true;
					}
					if(registro[i].garantia){
						registro[i].s.custo = 0;
						cout << "Aparelho ainda no perido de garantia\n";
					}
					else{
						cout << "Custo do servico: ";
						cin >> registro[i].s.custo;
					}
					registro[i].s.end = true;
					system("pause");
				}
			}
			if(!vef2){
				cout << "Identificador nao encontrado ou servico ja finalizado\n";
				vef2 = true;
				system("pause");
			}
			fflush_stdin();
		}
		
		if (menu == '3'){
			system("cls");
			cout << "Numero de identificacao: ";
			cin >> auxstr;
			auxint = atoi(auxstr);
			vef3 = false;
			for(i = 0; i < contador; i++){
				if((registro[i].id == auxint) && (registro[i].s.end == true)){
					vef3 = true;
					if(registro[i].s.finalizado){
						cout << "Pedido ja finalizado\n";
						system("pause");
						break;
					}
					if(registro[i].s.token){
						cout << "Pedido ja encerrado\n";
						system("pause");
						break;
					}					
					registro[i].s.token = true;
					if(registro[i].s.troca){
						cout << "Com defeito que exige troca\n";
					}
					else{
						cout << "Reparado sem exigir troca\n";
					}
					if(!registro[i].garantia){
						cout << "Custo do servico: " << registro[i].s.custo << "\n";
					}
					system("pause");
				}
			}
			if(!vef3){
				cout << "Identificador nao encontrado ou aparelho nao periciado\n";
				vef3 = true;
				system("pause");
			}
			fflush_stdin();			
		}
		
		if (menu == '4'){
			system("cls");
			cout << "Numero de identificacao: ";
			cin >> auxstr;
			auxint = atoi(auxstr);
			vef4 = false;
			for(i = 0; i < contador; i++){
				if((registro[i].id == auxint) && (!registro[i].s.pago) && (registro[i].s.end) && (registro[i].s.token)){
					if(registro[i].s.custo == 0){
						registro[i].s.pago = true;
						registro[i].s.finalizado = true;
						vef4 = true;
						cout << "Ordem completa! Nao necesita de pagamento\n";
						system("pause");
						break;
					}
					vef4 = true;
					if(registro[i].s.finalizado){
						cout << "Pedido ja finalizado\n";
						system("pause");
						break;
					}
					if(registro[i].garantia){
						cout << "Pagamento recusado (aparelho ainda esta no periodo de garantia)\n";
					}
					else{
						cout << "Valor pago: " << registro[i].s.custo << "\n";
					}
					registro[i].s.pago = true;
					registro[i].s.finalizado = true;
					system("pause");
				}
			}
			if(!vef4){
				cout << "Identificador nao encontrado ou servico nao finalizado\n";
				vef4 = true;
				system("pause");
			}
			fflush_stdin();
		}
		if (menu == '5'){
			system("cls");
			cout << "Numero de identificacao: ";
			cin >> auxstr;
			auxint = atoi(auxstr);
			vef5 = false;
			for(i = 0; i < contador; i++){
				if(registro[i].id == auxint){
					system("cls");
					cout << "Cliente: " << registro[i].nome << "\n";
					cout << "Modelo: " << registro[i].modelo << "\n";

					if((registro[i].s.end)){
						if(registro[i].s.troca){
							cout << "Aparelho novo\n";
						}
						else{
							cout << "Aparelho reformado\n";
						}
						if(registro[i].s.token){
							cout << "Pedido finalizado\n";
							if(registro[i].s.pago){
								cout << "Pedido pago\n";
							}
							else{
								cout << "Pagamento nao realizado. Valor: " << registro[i].s.custo << "\n";
							}
						}
						else{
							cout << "Pedido em andamento\n";
						}						
					}
					else{
						cout << "Pedido em andamento\n";
					}
					
				}
			}
			system("pause");
		}
		
		if(menu == '6'){
			while(1){
				system("cls");
				if(contador == 0){
					cout << "Nenhuma ordem cadastrada!\n";
					system("pause");
					break;
				}
				cout << "a)Percentual de ordens de servicos por tipo de problema relatado\n";
				cout << "b)Percentuais de ordens de servico de aparelhos que ainda se encontram no período de garantia\n";
				cout << "c)Relacao de numeros de identificacao das ordens de servico em aberto\n";
				cout << "d)Relacao de numeros de identificacao das ordens de servico encerradas\n";
				cout << "e)Relacao de numeros de identificacao das ordens de servico encerradas e com pagamento de serviços de reparo em aberto\n";
				cout << "Opcao: ";
				cin >> segundomenu;
				if(segundomenu == 'a'){
					a = 0;
					b = 0;
					c = 0;
					d = 0;
					e = 0;
					f = 0;
					g = 0;
					h = 0;
					for(i = 0; i < contador; i++){
						if(registro[i].problema == 'a'){
							a += 100/contador; 
						}
						if(registro[i].problema == 'b'){
							b += 100/contador;
						}
						if(registro[i].problema == 'c'){
							c += 100/contador;
						}
						if(registro[i].problema == 'd'){
							d += 100/contador;
						}
						if(registro[i].problema == 'e'){
							e += 100/contador;
						}
						if(registro[i].problema == 'f'){
							f += 100/contador;
						}
						if(registro[i].problema == 'g'){
							g += 100/contador;
						}
						if(registro[i].problema == 'h'){
							h += 100/contador;
						}						
					}
					system("cls");
					cout << "Percentuais de ordens de servico por tipo de problema\n";
					cout.precision(2);
					cout << fixed << "a)" << sa << ": " << a << "%\n";
					cout.precision(2);
					cout << fixed << "b)" << sb << ": " << b << "%\n";
					cout.precision(2);
					cout << fixed << "c)" << sc << ": " << c << "%\n";
					cout.precision(2);
					cout << fixed << "d)" << sd << ": " << d << "%\n";
					cout.precision(2);
					cout << fixed << "e)" << se << ": " << e << "%\n";
					cout.precision(2);
					cout << fixed << "f)" << sf << ": " << f << "%\n";
					cout.precision(2);
					cout << fixed << "g)" << sg << ": " << g << "%\n";
					cout.precision(2);
					cout << fixed << "h)" << sh << ": " << h << "%\n";
					system("pause");
					break;
				}
				if(segundomenu == 'b'){
					system("cls");
					a = 0;
					b = 0;
					for(i = 0; i < contador; i++){
						if(registro[i].garantia){
							a += 100/contador;							
						}
						else{
							b += 100/contador;
						}
					}
					cout << "Percentuais de ordens de servico que ainda se encontram na garantia\n";
					cout.precision(2);
					cout << fixed << "a) Porcentagem de aparelhos no periodo de garantia: " << a << "%\n";
					cout.precision(2);
					cout << fixed << "b) Porcentagem de aparelhos fora do periodo de garantia: " << b << "%\n";
					system("pause");
					break;
				}
				if(segundomenu == 'c'){
					system("cls");
					for(i = 0; i < contador; i++){
						if((!registro[i].s.token)){
							cout << "-----------------------------------\n";
							cout << "Numero de identificacao: " << registro[i].id << "\n";
							cout << "Cliente: " << registro[i].nome << "\n";
							cout << "Modelo: " << registro[i].modelo << "\n";
							cout << "Problema: ";
							if(registro[i].problema == 'a'){
								cout << sa << "\n";  
							}
							if(registro[i].problema == 'b'){
								cout << sb << "\n";
							}
							if(registro[i].problema == 'c'){
								cout << sc << "\n";
							}
							if(registro[i].problema == 'd'){
								cout << sd << "\n";
							}
							if(registro[i].problema == 'e'){
								cout << se << "\n";
							}
							if(registro[i].problema == 'f'){
								cout << sf << "\n";
							}
							if(registro[i].problema == 'g'){
								cout << sg << "\n";
							}
							if(registro[i].problema == 'h'){
								cout << sh << "\n";
							}
						}
					}
					cout << "-----------------------------------\n";
					system("pause");
					break;
				}
				if(segundomenu == 'd'){
					system("cls");
					for(i = 0; i < contador; i++){
						if((registro[i].s.token) && (registro[i].s.pago)){
							cout << "-----------------------------------\n";
							cout << "Numero de identificacao: " << registro[i].id << "\n";
							cout << "Cliente: " << registro[i].nome << "\n";
							cout << "Modelo: " << registro[i].modelo << "\n";
							if(registro[i].s.troca){
								cout << "Aparelho trocado\n";
							}
							else{
								cout << "Aparelho reformado\n";
							}
							if(!registro[i].garantia){
								cout << "Custo: " << registro[i].s.custo << "\n";
							}
							cout << "Pago!\n";
						}
					}
					cout << "-----------------------------------\n";
					system("pause");
					break;
				}
				if(segundomenu == 'e'){
					system("cls");
					for(i = 0; i < contador; i++){
						if((registro[i].s.token) && (!registro[i].s.pago)){
							cout << "-----------------------------------\n";
							cout << "Numero de identificacao: " << registro[i].id << "\n";
							cout << "Cliente: " << registro[i].nome << "\n";
							cout << "Modelo: " << registro[i].modelo << "\n";
							if(!registro[i].garantia){
								cout << "Custo: " << registro[i].s.custo << "\n";
							}
							cout << "Em aberto!\n";
						}
					}
					cout << "-----------------------------------\n";
					system("pause");
					break;
				}
			}
		}			
	}		
	return 0;
}
