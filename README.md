# Status Fetch
### Automatically update your Github status according to the OS you are using!

## Requirement
- `libcurl`

## Usage
1. On [Github](https://github.com/settings/tokens), create a **classic** token with `user` permission
2. Create and copy the token into `.env` file. Format: `GITHUB_TOKEN=...`
3. Compile or download binary of the app. Make sure `.env` file is under the same folder of the executable
4. Use `run.sh` (Bash on Linux) or `run.ps1` (PowerShell on Windows) to load .env and run executable automatically

> [!IMPORTANT]  
> - Your main executable should have the name `statusfetch` (Linux) or `statusfetch.exe` (Windows) in order for the script to find the executable
> 
> - `.env`, `run.sh/ps1` and `statusfetch(.exe)` should be under the same folder
> 
> - Make sure your .env file has the least permission (typically 400) to ensure security of your token

> [!TIP]
> You may also configure the app to run at startup. As long as you configure environmental variable correctly, you may run the executable directly, without needing the scripts
