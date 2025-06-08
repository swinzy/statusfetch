# Load .env
if (Test-Path ".env") {
    Get-Content ".env" | ForEach-Object {
        if ($_ -match '^\s*([^#][^=]+)=(.+)$') {
            $key = $matches[1].Trim()
            $val = $matches[2].Trim()
            [System.Environment]::SetEnvironmentVariable($key, $val, "Process")
        }
    }
} else {
    Write-Error "No .env file. Please create .env file and put GITHUB_TOKEN=... Make sure you have the least permission for security purpose."
    exit 1
}

# Point to executable
Start-Process -NoNewWindow -FilePath ".\statusfetch.exe" -Wait

