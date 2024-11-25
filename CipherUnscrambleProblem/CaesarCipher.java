public class CaesarCipher{
    StringBuilder string = new StringBuilder();
    public String Ciphering(String flag, int cipherShift){
        for(int i=0; i<flag.length(); i++){
            char character= flag.charAt(i);
            if(character>='A'&& character<='Z'){
                char letter= (char)(((character-'A'+cipherShift)%26 + 26)%26+'A');
                string.append(letter);
            }
            if(character>='a'&& character<='z'){
                char letter= (char)(((character-'a'+cipherShift)%26 + 26)%26+'a');    
                string.append(letter);
            }
        }
        return string.toString();
    }
    
}    
