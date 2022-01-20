# Configurações do PowerShell
# Importar os temas do oh-my-posh e utilizar o Star
Import-Module posh-git
Import-Module oh-my-posh
Set-PoshPrompt powerlevel10k_rainbow

# Autocomplete, keybinds e histórico de comandos
Set-PSReadlineKeyHandler -Key Tab -Function MenuComplete
Set-PSReadLineKeyHandler -Key UpArrow -Function HistorySearchBackward
Set-PSReadLineKeyHandler -Key DownArrow -Function HistorySearchForward
Set-PSReadlineOption -HistorySearchCursorMovesToEnd

# Autosugestões do PSReadline
Set-PSReadlineOption -ShowToolTips
Set-PSReadlineOption -PredictionSource History
