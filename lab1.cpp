#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;


class Music{
	unsigned int year;
	string artist_name;
	string music_ID;
	
public:
	Music() : year (0){
	}

	Music(unsigned int yr,string artist,string ID){
		year = yr;
		artist_name = artist;
		music_ID = ID;
	}
	
	bool operator == (const Music& target){ 
		bool are_equal = year == target.year;
		are_equal = are_equal && artist_name == target.artist_name;
		are_equal = are_equal && music_ID == target.music_ID;
		return are_equal;
	}

	string get_artist(){
		return artist_name;
	}
};

class Song : public Music{
	string genre,song_name;
	unsigned int song_length;
	Music mus;
	
public:
	Song() : song_length(0){
	}
	Song(string gen,string name, unsigned int length, Music m){	
	genre = gen;
	song_name = name;
	song_length = length;		
	mus = m;
	}
	
	string get_song(){
		return song_name;
	}
	
	bool operator == (const Song& target){
		bool are_equal = static_cast<Music>(target) == static_cast<Music>(*this);
		are_equal = are_equal && genre == target.genre;
		are_equal = are_equal && song_name == target.song_name;
		are_equal = are_equal && song_length == target.song_length;
		
		return are_equal;
		
	}
	
	string get_a(){
		return mus.get_artist();
	}


};


class Playlist{
	
public:
	vector <Song> my_playlist;
	
		
	bool insert_song(Song& song_info){
		int count_song = 0;
		int count_artist = 0;
	
		for (int i = 0; i<my_playlist.size();i++){
			
			if (my_playlist[i]==song_info){
				count_song = count_song + 1;
			}
			if (my_playlist[i].get_a()==song_info.get_a()){
				count_artist = count_artist + 1;
			}
		}

		if (count_song == 0 && count_artist < 3){
			my_playlist.push_back(song_info);	
			return true;
		}else{
			return false;
		}
	//	my_playlist.push_back(song_info); test
	}
	
	
	void shuffle_songs(){
		Song temp ;
		int randomIndex =0;
		
		for(int i=0;i<my_playlist.size();i++){
			randomIndex = rand()% my_playlist.size();
			temp = my_playlist[i];
			my_playlist[i] = my_playlist[randomIndex];
			my_playlist[randomIndex] = temp;	
		}	
	}
	
	friend Playlist operator+(Playlist &playlist1,Playlist &playlist2);
	
	
};

Playlist operator+(Playlist &playlist1,Playlist &playlist2){
	Playlist temp;
	
	for (int i = 0 ;i<playlist1.my_playlist.size();i++){
		temp.my_playlist.push_back(playlist1.my_playlist[i]);
	}
	for (int i = 0; i<playlist2.my_playlist.size();i++){
		temp.my_playlist.push_back(playlist2.my_playlist[i]);
	}
	
	return temp;

}

// driver function to test

class run_test {

    Music m0, m1, m2,m3, m4;
    Song s0, s1, s2, s3, s4, s5;
    Playlist p;

public:

    void test_music () {
        m0 = Music();
        m1 = Music(1997, "Eminem", "200");
        m2 = Music(2005, "MJ", "400");
        m3 = Music(1997, "Eminem", "200");
        m4 = Music (2005, "Taylor Swift", "500");
    	cout << m1.get_artist() << endl;
    	cout << (m1 == m2) << endl;
    	cout << (m1 == m3) << endl;
    	cout << endl;
    	cout << endl;
    }



    void test_songs () {
        s0 = Song ("rap", "Mockingbird", 300, m1);
        s1 = Song ("pop", "Pressure", 250, m2 );
        s2 = Song ("rap", "Mockingbird", 300, m1);
        s3 = Song ("pop", "Stan", 400, m1);
        s4 = Song ( "Country", "1989", 500, m4);
        s5 = Song ("Country", "Red", 500, m4);
        cout << s1.get_song() << endl;
    	cout << (s1 == s2) << endl;
    	cout << (s1 == s3) << endl;
    	cout << endl;
    	cout << endl;
    }

   

    void test_insert_songs () {
        p.insert_song (s0);
        p.insert_song (s1);
        p.insert_song (s2);
        p.insert_song (s3);
        p.insert_song (s4);
    }

    void test_shuffle_songs () {
        p.shuffle_songs ();
    }

    void display_songs (){
        for (int i = 0; i < p.my_playlist.size(); i++) {
            cout << p. my_playlist[i].get_song() << endl;
        }
        cout << endl;
    	cout << endl;
    }

};

int main (){
	srand(time(0));

	run_test rt;

	rt. test_music();
	rt. test_songs();
	rt. test_insert_songs();
	rt. display_songs (); // Display Songs before shuffle
	rt. test_shuffle_songs();
	rt. display_songs (); // Display songs after shuffle

	return 0;
}

