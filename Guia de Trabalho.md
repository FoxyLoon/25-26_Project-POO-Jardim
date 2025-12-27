Grelha = Jardim
	- Constituido por conjunto de posições (bocados de solo):
		- Solo Vazio
			Cada posição tem caracteristicas diferentes:
			- Valores aleatórios de água (começa entre 80 a 100)
			- Valores aleatórios de nutrientes (começa entre 40 a 50)
			- Não há limites especificos para as caracteristicas do solo (pode atingir valores gigantescos)
			
		- Planta
			- Pode ou não pode ter (0 ou 1)
		- Ferramenta
			- Pode ou não pode ter (0 ou 1)
  			- 3 ferramentas aleatorias postas no jardim.
		
		- Jardineiro
			- Pode ou não estar presente no jardim
				- Se estiver presente, tem que estar numa posição da grelha, não pode estar fora.
	
	Maximo de grelha 26x26 (letras do alfabeto). Nao pode ser 0x0 ou menor

	Ordem de Prioridade a mostrar na grelha:
		1. Jardineiro
		2. Planta
		3. Ferramenta
   

Utilizador = Jardineiro
	- Aparece na Grelha em forma de asterisco (*);
    	- Aparece sobreposto a tudo o resto
	- Podes-se deslocar na Grelha
    	- Desloca-se para posições vizinhas:
        	- Cima
        	- Baixo
        	- Esquerda
        	- Direita
	- Pode Sair da Grelha;
	- Pode voltar a entrar na grelha sempre que desejar
	- Pode transportar ferramentas:
		- Regador, Saco de Adubo;
		- Só pode usar uma ferramenta de cada vez
    		- Ferramenta na mão significa que esta ativa
    		- Ação da ferramenta acontece automaticamente por cada instante
    		- Ação da ferramenta acontece APENAS na posição de aonde o jardineiro está. Ação não para após ser executada até ao fim.
    		- Ações deixam de ser executadas quando a ferramenta sair da mão do jardineiro (apesar de ainda poder estar na posse do jardineiro).
            	- Não é obrigado a ter ferramentas na mão (só está "a ver")
    		- Pode mudar de ferramenta a qualquer momento (exceto enquanto está a ser executada)
    		- O jardineiro pode transportar quantas ferramentas quiser (sem limite)
  		- Ferramentas só são obtidas:
    		- Ao serem encontradas no jardim
        		- Ferramentas são automaticamente apanhadas assim que o jardineiro passar pela posição no qual se encontra a ferramenta.
        		- Não é importante se a ferramenta está visivel ou não (por causa da ordem de prioridade de visibilidade)
        		- Sempre que uma ferramenta é apanhada, uma nova ferramenta aleatoria aparece numa posição aleatória (não pode aparecer por cima do proprio jardineiro.)
      		- Ao "comprar online"
        		- Compra efetuada por comando do utilizador
	- Pode solcitar informações adicionais sobre "determinados aspetos" (é o que está escrito no enunciado, página 6, 3ºParagrafo, "Funcionamento e uso do simulador")

Ferramentas
	- Desempenham ações especificas da ferramenta
	- Contem numero de série
    	- Identificador unico de cada ferramenta
        	- Identificador é atribuido no momento da sua criação
        	- A primeira tem numero 1
    	- Valor crescente
  	- Ferramentas disponiveis:
    	- Regador (g)
        	- Aumenta a quantidade de água em 10 unidades da posição em que o jardineiro se encontra.
        	- Capacidade Inicial = 200 unidades de água
        	- Quando fica vazio:
            	- Regador torna-se inutil
            	- Jardineiro fica frustado
            	- Regador é atirado para tão longe que sai do simulador
      	- Pacote de Adubo (a)
        	- Aumenta a quantidade de nutrientes do solo em 10 unidades da posição que o jardineiro se encontra
        	- Capacidade Inicial = 100 unidades de nutrientes
        	- Quanto terminar as unidades, terminou!
        	- Quando fica vazio:
            	- Pacote fica super leve
            	- Voa com o vento para o quintal do vizinho
            	- Deixa de ser um problema para o Jardineiro/Utilizador
      	- Tesoura de Poda(t)
        	- Podem cortar cachos de uvas das videiras
        	- Eliminam todas as plantas consideradas como "feias" se estiver na mão do jardineiro.
        	- Tesoura nunca se desgasta
        	- Material -> Feito de Aço Cromado
            	
      	- FerramentaZ (z) (necessário rever)
        	- Ferramenta tecnológica avançada que equilibra o solo para condições ideais.
        	- Analisa o solo e ajusta água e nutrientes para valores ótimos
            - Valores ótimos: água = 90, nutrientes = 45
            - Cada uso consome 1 carga de bateria
            - Capacidade: 50 cargas
        	- Quando a bateria acaba, deve ser reciclada
			- Settings:
            	- Se água < 90: adiciona até 15 unidades (aproxima do ótimo)
            	- Se água > 90: remove até 15 unidades (aproxima do ótimo)
              	- Se nutrientes < 45: adiciona até 10 unidades
            	- Se nutrientes > 45: remove até 10 unidades


Plantas
	- Constituida por várias espécies
  	- Todas as espécies têm algumas caracteristicas em comum (Herança)
  	- Todas as espécies também têm as suas próprias características e comportamentos únicos
  	- Cada uma tem a sua própria reserva...
    	- ...De nutrientes
    	- ...De água
  	- Plantas podem RETIRAR água e nutrientes do solo
	- Plantas podem COLOCAR água e nutrientes no solo
	- Plantas têm um atributo de beleza:
    	- Feia
    	- Bonita
    	- Neutra
    	- (não há mais nenhum outro atributo de beleza para além destes três)
  	
	
	- Plantas Disponíveis:
    	- Cacto (c)
        	- Beleza = Neutra
            
			- Começa no seu deposito
    			- (Não especificado)
        	
			- A cada instante:
            	- Absorve 25% de água existente no solo
            	- Absorve até 5 unidades de nutrientes do solo (valor random de 1 a 5)
          	
			- Condição de Morte:
            	- Se o solo tiver mais que 100 unidades de água em 3 instantes seguidos, morre
            	- Se o solo tiver 0 nutrientes durante 3 instantes seguidos, morre
          	
			- Pós-Morte:
            	- Deposita os nutrientes do seu depósito/reserva no solo em que está
            	- Água do seu depósito desaparece (a água que ainda está no solo mantêm-se)
            	
			- Multiplicação:
    			- SE 
        			- houver uma posição aleatória vizinha vazia
    				- Nutrientes do depósito do Cacto original > 100 !!!
    				- Água do depósito do Cacto original > 50 !!!

				- ENTÃO
    				- Nasce um cacto na posição vizinha escolhida.
    				- Os nutrientes do cacto original são dividos em 2. Metade para o cacto original e a outra metade para o novo cacto
    	
		- Roseira (r)
    		- Beleza = Bonita
      		
			- Começa no seu deposito:
    			- Nutrientes = 25
    			- Água = 25

			- A cada instante:
    			- Perde 4 unidades de água
    			- Perde 4 unidades de nutrientes
    			- Absorve 5 unidades de água do solo (se existir)
    			- Absorve 8 unidades de nutrientes do solo (se existir)

			- Condições de Morte
    			- Se a quantidade de água do seu depósito <= 0
    			- Se a quantidade de nutrientes do seu depósito <= 0
    			- Se a quantidade de nutrientes do seu depósito >= 200
    			- Se todas as posições vizinhas tiverem uma planta
			
			- Pós-Morte
    			- Deixa metade dos nutrientes do seu depósito no solo
    			- Deixa metade da água do seu depósito no solo
  			
			- Multiplicação:
    			- SE
        			- Houver posição aleatória vizinha vazia
        			- Nutrientes do Depósito da Roseira > 100
        			- Água não é tomada em consideração

    			- ENTÃO
        			- Nasce Nova Roseira com:
            			- Nutrientes = 25
            			- Água = (Água da Roseira Original) / 2
        			- E Roseira Original fica com:
            			- Nutrientes = 100
            			- Água = (Água da Roseira Original) / 2
    	
		- Erva Daninha (e)
    		- Beleza = Feia
    		
			- Começa no seu depósito:
    			- Nutrientes = 5
    			- Água = 5
    		
			- A cada instante:
    			- Absorve 1 unidades de água do solo (se existir)
    			- Absorve 1 unidades de nutrientes do solo (se existir)
  			
			- Condições de Morte
    			- Após 60 instantes
    		
			- Pós-Morte
    			- (Não especificado)
  			
			- Multiplicação:
    			- SE
        			- Houver posição aleatória vizinha vazia 
        			- Houver posição aleatória vizinha com planta
        			- Nutrientes > 30 && 5 instantes seguidos
        			- 
      			
  				- ENTÃO
    				- Se houver planta na posição escolhida, mata a planta e substitui
    				- Se não houver planta, apenas ocupa o espaço normalmente
    				- Nova Erva Daninha fica:
        				- Água = 5
        				- Nutrientes = 5
      				- E a Erva Daninha original fica:
        				- Igual - não há mudanças
		
		- Planta Exótica (x) - BAMBU LUNAR
		Planta exótica importada de um país distante no Oriente.

        	- Beleza: BONITA
        	
			- Começa no seu depósito:
				- Água = 30
				- Nutrientes = 30
    		
			- Ciclos de crescimento:
            	- Jovem: 0-20 instantes (absorve recursos)
            	- Adulta: 21-40 instantes (equilíbrio)
            	- Madura: 41+ instantes (produz nutrientes)
        	
			- A cada instante:
    			- Fase Jovem:
        			- Absorve 3 unidades de água do solo (se existir)
                	- Absorve 2 unidades de nutrientes do solo (se existir)
              	
				- Fase Adulta:
                	- (Apenas existe e não faz nada)
              	
				- Fase Madura:
                	- Produz 2 unidades de nutrientes para o solo
                	- Perde 2 unidades de água
                	- Perde 1 unidade de nutrientes

			- Condições de Morte
            	- Água interna < 5
            	- Nutrientes internos < 3
            	- Após 80 instantes (ciclo de vida completo)
    		
			- Pós-Morte
    			- Deixa 75% dos seus recursos no solo

        	- Multiplicação:
            	- SE:
                	- Houver posições diagonais disponiveis vazias (NE, SE, SW, NW)
                	- Nutrientes da Exotica original > 70
                	- Água da Exotica Original > 60
              	- ENTÃO:
                  	- Nova Exotica fica:
                    	- Água = 30
                    	- Nutrientes = 30
                  	- E Exotica Original fica:
                    	- Metade dos recursos que tinha no seu deposito

Simulador
	- Simula Tempo:
		- Tempo Afeta Crescimento das plantas
		- Tempo Afeta Multiplicação das plantas
		- Tempo Afeta Morte das Plantas
		
		- Tempo definido por Instantes
			- Cada instante passa por cada ação do jogador (dar o comando "avança" na consola)
			- Instantes apenas crescem sem limites
			- Instantes nunca decrescem
			- Verificar a cada instante se o Jardineiro tem uma ferramenta e se tiver, executar a sua ação automaticamente.
			- Verificar em cada instante se o jardineiro possui a ferramenta "Tesoura de Poda" na mão e se na posição em que o jardineiro está, se está uma planta considerada como "feia", eliminá-la!
			- Plantas podem desempenhar comportamentos unicos a cada instante dependendo de:
				- Espécie
				- Caracteristicas do Jardim
				- Outros Fatores
		
		- Consequencias de cada ação devem ser mostradas imediatamente após cada instante
	
	- A cada turno/instante:
    	- Deverá ser mostrado informação
        	- Plantas que morreram
        	- Plantas que apareceram
        	- Nova representação do jardim
  	

	- Termina quando o Utilizador assim decidir