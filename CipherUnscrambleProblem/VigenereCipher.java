public class VigenereCipher{
    StringBuilder string = new StringBuilder();
    public String Cipher(String newFlag, String shiftKey){
        int[] character = new int[27];
            for(int i=0; i<newFlag.length(); i++){
                character[i]= shiftKey.charAt(i%2);
                if(newFlag.charAt(i)>='A'&& newFlag.charAt(i)<='Z'){
                    char letter= (char)(newFlag.charAt(i) + character[i]);
                    if(letter>='A' && letter<='Z'){
                        string.append((char)((newFlag.charAt(letter))));
                    }
                    else{
                        string.append((char)((newFlag.charAt(letter))-26));
                    }
                }
                if(newFlag.charAt(i)>='a'&& newFlag.charAt(i)<='z'){
                    char letter= (char)(newFlag.charAt(i)+character[i]);
                    if(letter>='a'&& letter<='z'){
                        string.append((char)((newFlag.charAt(letter))));   
                    }
                    else{
                        string.append((char)((newFlag.charAt(letter))-26));
                    }
                }
            }
            return string.toString();
    }

}