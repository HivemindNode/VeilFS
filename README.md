# VeilFS  
_A volatile, self-destructing filesystem for secure, ephemeral storage._  

### What It Does:  
- **Creates an encrypted RAM-based filesystem that never writes to disk**  
- **Automatically erases files after a defined expiration time**  
- **Uses self-destruction triggers to permanently wipe all data**  
- **Ensures no data recovery, even with forensic tools**  

### Who Is It For?  
_"A file that is gone before you look  
Is a file that was never there."_  

### How to Use:  
1. Mount **VeilFS** to create a volatile storage environment:  
   ```bash
   ./veilfs --mount /mnt/veil
