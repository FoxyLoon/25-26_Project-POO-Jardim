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
    		- Ação da ferramenta acontece APENAS na posição de aonde está.
		

Ferramentas
	- Desempenham ações especificas da ferramenta
	

Simulador
	- Simula passagem de tempo
		- Afeta Crescimento das plantas
		- Afeta Multiplicação das plantas
		- Afeta Morte das Plantas
		
		- Tempo definido por Instantes
			- Cada instante passa por cada ação do jogador (dar um comando na consola)
			- A cada instante, deverá verificar se o Jardineiro tem uma ferramenta e se tiver, executar a sua ação automaticamente.
			- Plantas podem desempenhar comportamentos unicos a cada instante dependendo de:
				- Espécie
				- Caracteristicas do Jardim
				- Outros Fatores
	
	- Termina quando o Utilizador decidir