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
            	
      	- FerramentaZ (z)
        	- (Ainda por definir)
	

Simulador
	- Simula passagem de tempo
		- Afeta Crescimento das plantas
		- Afeta Multiplicação das plantas
		- Afeta Morte das Plantas
		
		- Tempo definido por Instantes
			- Cada instante passa por cada ação do jogador (dar um comando na consola)
			- Verificar a cada instante se o Jardineiro tem uma ferramenta e se tiver, executar a sua ação automaticamente.
			- Verificar em cada instante se o jardineiro possui a ferramenta "Tesoura de Poda" na mão e se na posição em que o jardineiro está, se está uma planta considerada como "feia", eliminá-la!
			- Plantas podem desempenhar comportamentos unicos a cada instante dependendo de:
				- Espécie
				- Caracteristicas do Jardim
				- Outros Fatores
	
	- Termina quando o Utilizador assim decidir