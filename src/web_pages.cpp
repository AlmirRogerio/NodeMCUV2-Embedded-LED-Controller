#include "web_pages.h"
#include <ESP8266WiFi.h>

namespace WebPages
{

String configPage()
{
    String networks = "";
    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; i++)
    {
        networks += "<option value=\"" + WiFi.SSID(i) + "\">"
                  + WiFi.SSID(i) + " (" + String(WiFi.RSSI(i)) + " dBm)</option>";
    }

    return R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>NodeMCU - Configuração WiFi</title>
<style>
*{margin:0;padding:0;box-sizing:border-box;font-family:Inter,Segoe UI,Arial,sans-serif;}
body{min-height:100vh;display:flex;justify-content:center;align-items:center;background:radial-gradient(circle at top,#27374d,#111827 70%);color:#e5e7eb;}
.card{width:380px;padding:35px;border-radius:22px;background:rgba(30,41,59,.85);backdrop-filter:blur(18px);border:1px solid rgba(255,255,255,.08);box-shadow:0 15px 35px rgba(0,0,0,.25);}
h1{font-size:26px;font-weight:600;margin-bottom:8px;}
.subtitle{color:#9ca3af;font-size:14px;margin-bottom:25px;}
label{display:block;margin-bottom:6px;font-size:14px;color:#9ca3af;}
select,input{width:100%;height:44px;border:1px solid rgba(255,255,255,.15);border-radius:10px;background:rgba(15,23,42,.8);color:#e5e7eb;padding:0 12px;font-size:15px;margin-bottom:18px;outline:none;}
select:focus,input:focus{border-color:#2563eb;}
button{width:100%;height:48px;border:none;border-radius:14px;background:#2563eb;color:white;font-size:16px;font-weight:600;cursor:pointer;transition:.2s;}
button:hover{background:#3b82f6;}
button:active{transform:scale(.98);}
.footer{margin-top:20px;color:#6b7280;font-size:12px;text-align:center;}
.manual{margin-top:10px;font-size:13px;color:#60a5fa;cursor:pointer;text-align:center;}
#manualInput{display:none;}
</style>
</head>
<body>
<div class="card">
<h1>⚙️ WiFi Setup</h1>
<div class="subtitle">Selecione a rede e digite a senha para conectar o NodeMCU.</div>
<form action="/save" method="POST">
<label for="ssid">Rede WiFi</label>
<select name="ssid" id="ssidSelect">
)rawliteral" + networks + R"rawliteral(
</select>
<div class="manual" onclick="document.getElementById('manualInput').style.display='block';document.getElementById('ssidSelect').style.display='none';this.style.display='none';">
Digitar manualmente
</div>
<input type="text" name="ssid_manual" id="manualInput" placeholder="Nome da rede (SSID)">
<label for="password">Senha</label>
<input type="password" name="password" id="password" placeholder="Senha da rede">
<button type="submit">Conectar</button>
</form>
<div class="footer">NodeMCU WiFi Manager</div>
</div>
</body>
</html>
)rawliteral";
}

String successPage()
{
    return R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>NodeMCU - Salvo!</title>
<style>
*{margin:0;padding:0;box-sizing:border-box;font-family:Inter,Segoe UI,Arial,sans-serif;}
body{min-height:100vh;display:flex;justify-content:center;align-items:center;background:radial-gradient(circle at top,#27374d,#111827 70%);color:#e5e7eb;}
.card{width:380px;padding:35px;border-radius:22px;background:rgba(30,41,59,.85);backdrop-filter:blur(18px);border:1px solid rgba(255,255,255,.08);box-shadow:0 15px 35px rgba(0,0,0,.25);text-align:center;}
h1{font-size:26px;font-weight:600;margin-bottom:12px;}
p{color:#9ca3af;font-size:15px;line-height:1.6;}
</style>
</head>
<body>
<div class="card">
<h1>✅ Salvo!</h1>
<p>Credenciais salvas com sucesso.<br>O NodeMCU irá reiniciar e conectar na rede selecionada.</p>
</div>
</body>
</html>
)rawliteral";
}

String controlPage(const String& ipAddress)
{
    return R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>NodeMCU Control</title>
<style>
*{margin:0;padding:0;box-sizing:border-box;font-family:Inter,Segoe UI,Arial,sans-serif;}
body{min-height:100vh;display:flex;justify-content:center;align-items:center;background:radial-gradient(circle at top,#27374d,#111827 70%);color:#e5e7eb;}
.card{width:380px;padding:35px;border-radius:22px;background:rgba(30,41,59,.85);backdrop-filter:blur(18px);border:1px solid rgba(255,255,255,.08);box-shadow:0 15px 35px rgba(0,0,0,.25);}
h1{font-size:30px;font-weight:600;}
.subtitle{margin-top:8px;color:#9ca3af;font-size:15px;}
.status{margin:35px auto;width:180px;height:52px;border-radius:999px;display:flex;align-items:center;justify-content:center;gap:12px;font-size:17px;font-weight:500;transition:.3s;}
.status::before{content:"";width:12px;height:12px;border-radius:50%;background:currentColor;}
.off{background:#2d3748;color:#ef4444;}
.on{background:#1f3d2d;color:#22c55e;}
button{width:100%;height:48px;border:none;border-radius:14px;background:#2563eb;color:white;font-size:16px;font-weight:600;cursor:pointer;transition:.2s;}
button:hover{background:#3b82f6;}
button:active{transform:scale(.98);}
.btn-reset{margin-top:12px;background:#dc2626;font-size:13px;height:38px;border-radius:10px;}
.btn-reset:hover{background:#ef4444;}
.footer{margin-top:25px;color:#6b7280;font-size:13px;text-align:center;}
.ip-info{margin-top:8px;color:#6b7280;font-size:12px;text-align:center;}
</style>
</head>
<body>
<div class="card">
<h1>ESP8266</h1>
<div class="subtitle">Controle do LED onboard</div>
<div id="status" class="status off">Desligado</div>
<button onclick="toggle()">Alternar LED</button>
<button class="btn-reset" onclick="if(confirm('Apagar credenciais WiFi e reiniciar?'))fetch('/reset-wifi').then(()=>alert('Reiniciando...'))">Resetar WiFi</button>
<div class="footer">NodeMCU Web Server</div>
<div class="ip-info">)rawliteral" + ipAddress + R"rawliteral(</div>
</div>
<script>
function atualizar(){fetch("/status").then(r=>r.text()).then(t=>{let s=document.getElementById("status");if(t=="LED LIGADO"){s.className="status on";s.innerHTML="Ligado";}else{s.className="status off";s.innerHTML="Desligado";}});}
function toggle(){fetch("/toggle").then(()=>{atualizar();});}
atualizar();
</script>
</body>
</html>
)rawliteral";
}

}
