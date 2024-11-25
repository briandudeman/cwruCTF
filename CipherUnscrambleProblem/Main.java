protected class Main{
    public static void main(String[] args){
        String flag= "CASEWesternReserveUCiphered";
        int cipherShift= 1826;
        String shiftKey= "DO";
        CaesarCipher caesarCipher = new CaesarCipher();
        String newFlag= caesarCipher.Ciphering(flag, cipherShift);
        System.out.println(newFlag);
        VigenereCipher vigenereCipher = new VigenereCipher();
        newFlag= vigenereCipher.Cipher(newFlag, shiftKey);
        System.out.println("DO try your best to decode this key: " + newFlag);

    }
}