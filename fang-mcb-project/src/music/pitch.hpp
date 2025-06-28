#ifndef FANG_ROBOTICS_MCB_MUSIC_PITCH_HPP
#define FANG_ROBOTICS_MCB_MUSIC_PITCH_HPP
namespace music
{
    //Add ease of conversion by allowing implicit
    enum BasicPitch
    {
        C   = 0,
        Cs  = 1,
        Db  = 1,
        D   = 2,
        Ds  = 3,
        Eb  = 3,
        E   = 4,
        F   = 5,
        Fs  = 6,
        Gb  = 6,
        G   = 7,
        Gs  = 8,
        Ab  = 8,
        A   = 9,
        As  = 9,
        Bb  = 10,
        B   = 11
    };

    constexpr int octaveSpace(int octaveNumber)
    {
        //https://soundprogramming.net/file-formats/midi-note-frequencies/
        return (12 * (octaveNumber + 2));
    }

    constexpr int firstOctaveSpace{octaveSpace(1)};
    constexpr int secondOctaveSpace{octaveSpace(2)};
    constexpr int thirdOctaveSpace{octaveSpace(3)};
    constexpr int fourthOctaveSpace{octaveSpace(4)};
    constexpr int fifthOctaveSpace{octaveSpace(5)};
    constexpr int sixthOctaveSpace{octaveSpace(6)};
    constexpr int seventhOctaveSpace{octaveSpace(7)};


    export enum class Pitch
    {
        C1      = C  + firstOctaveSpace,
        Cs1     = Cs + firstOctaveSpace,
        Db1     = Db + firstOctaveSpace,
        D1      = D  + firstOctaveSpace,
        Ds1     = Ds + firstOctaveSpace,
        Eb1     = Eb + firstOctaveSpace,
        E1      = E  + firstOctaveSpace,
        F1      = F  + firstOctaveSpace,
        Fs1     = Fs + firstOctaveSpace,
        Gb1     = Gb + firstOctaveSpace,
        G1      = G  + firstOctaveSpace,
        Gs1     = Gb + firstOctaveSpace,
        Ab1     = Ab + firstOctaveSpace,
        A1      = A  + firstOctaveSpace,
        As1     = As + firstOctaveSpace,
        Bb1     = Bb + firstOctaveSpace,
        B1      = B  + firstOctaveSpace, 
        //2nd octave
        C2      = C  + secondOctaveSpace,
        Cs2     = Cs + secondOctaveSpace,
        Db2     = Db + secondOctaveSpace,
        D2      = D  + secondOctaveSpace,
        Ds2     = Ds + secondOctaveSpace,
        Eb2     = Eb + secondOctaveSpace,
        E2      = E  + secondOctaveSpace,
        F2      = F  + secondOctaveSpace,
        Fs2     = Fs + secondOctaveSpace,
        Gb2     = Gb + secondOctaveSpace,
        G2      = G  + secondOctaveSpace,
        Gs2     = Gb + secondOctaveSpace,
        Ab2     = Ab + secondOctaveSpace,
        A2      = A  + secondOctaveSpace,
        As2     = As + secondOctaveSpace,
        Bb2     = Bb + secondOctaveSpace,
        B2      = B  + secondOctaveSpace, 
        //3rd octave
        C3      = C  + thirdOctaveSpace,
        Cs3     = Cs + thirdOctaveSpace,
        Db3     = Db + thirdOctaveSpace,
        D3      = D  + thirdOctaveSpace,
        Ds3     = Ds + thirdOctaveSpace,
        Eb3     = Eb + thirdOctaveSpace,
        E3      = E  + thirdOctaveSpace,
        F3      = F  + thirdOctaveSpace,
        Fs3     = Fs + thirdOctaveSpace,
        Gb3     = Gb + thirdOctaveSpace,
        G3      = G  + thirdOctaveSpace,
        Gs3     = Gb + thirdOctaveSpace,
        Ab3     = Ab + thirdOctaveSpace,
        A3      = A  + thirdOctaveSpace,
        As3     = As + thirdOctaveSpace,
        Bb3     = Bb + thirdOctaveSpace,
        B3      = B  + thirdOctaveSpace, 
        //4th octave
        C4      = C  + fourthOctaveSpace,
        Cs4     = Cs + fourthOctaveSpace,
        Db4     = Db + fourthOctaveSpace,
        D4      = D  + fourthOctaveSpace,
        Ds4     = Ds + fourthOctaveSpace,
        Eb4     = Eb + fourthOctaveSpace,
        E4      = E  + fourthOctaveSpace,
        F4      = F  + fourthOctaveSpace,
        Fs4     = Fs + fourthOctaveSpace,
        Gb4     = Gb + fourthOctaveSpace,
        G4      = G  + fourthOctaveSpace,
        Gs4     = Gb + fourthOctaveSpace,
        Ab4     = Ab + fourthOctaveSpace,
        A4      = A  + fourthOctaveSpace,
        As4     = As + fourthOctaveSpace,
        Bb4     = Bb + fourthOctaveSpace,
        B4      = B  + fourthOctaveSpace, 
        //5th octave
        C5      = C  + fifthOctaveSpace,
        Cs5     = Cs + fifthOctaveSpace,
        Db5     = Db + fifthOctaveSpace,
        D5      = D  + fifthOctaveSpace,
        Ds5     = Ds + fifthOctaveSpace,
        Eb5     = Eb + fifthOctaveSpace,
        E5      = E  + fifthOctaveSpace,
        F5      = F  + fifthOctaveSpace,
        Fs5     = Fs + fifthOctaveSpace,
        Gb5     = Gb + fifthOctaveSpace,
        G5      = G  + fifthOctaveSpace,
        Gs5     = Gb + fifthOctaveSpace,
        Ab5     = Ab + fifthOctaveSpace,
        A5      = A  + fifthOctaveSpace,
        As5     = As + fifthOctaveSpace,
        Bb5     = Bb + fifthOctaveSpace,
        B5      = B  + fifthOctaveSpace, 
        //6th octave
        C6      = C  + sixthOctaveSpace,
        Cs6     = Cs + sixthOctaveSpace,
        Db6     = Db + sixthOctaveSpace,
        D6      = D  + sixthOctaveSpace,
        Ds6     = Ds + sixthOctaveSpace,
        Eb6     = Eb + sixthOctaveSpace,
        E6      = E  + sixthOctaveSpace,
        F6      = F  + sixthOctaveSpace,
        Fs6     = Fs + sixthOctaveSpace,
        Gb6     = Gb + sixthOctaveSpace,
        G6      = G  + sixthOctaveSpace,
        Gs6     = Gb + sixthOctaveSpace,
        Ab6     = Ab + sixthOctaveSpace,
        A6      = A  + sixthOctaveSpace,
        As6     = As + sixthOctaveSpace,
        Bb6     = Bb + sixthOctaveSpace,
        B6      = B  + sixthOctaveSpace, 
        //7th octave
        C7      = C  + seventhOctaveSpace,
        Cs7     = Cs + seventhOctaveSpace,
        Db7     = Db + seventhOctaveSpace,
        D7      = D  + seventhOctaveSpace,
        Ds7     = Ds + seventhOctaveSpace,
        Eb7     = Eb + seventhOctaveSpace,
        E7      = E  + seventhOctaveSpace,
        F7      = F  + seventhOctaveSpace,
        Fs7     = Fs + seventhOctaveSpace,
        Gb7     = Gb + seventhOctaveSpace,
        G7      = G  + seventhOctaveSpace,
        Gs7     = Gb + seventhOctaveSpace,
        Ab7     = Ab + seventhOctaveSpace,
        A7      = A  + seventhOctaveSpace,
        As7     = As + seventhOctaveSpace,
        Bb7     = Bb + seventhOctaveSpace,
        B7      = B  + seventhOctaveSpace, 
    };
}
#endif