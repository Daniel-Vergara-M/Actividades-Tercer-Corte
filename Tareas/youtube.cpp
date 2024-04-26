#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct Video
{

    string title;
    int favorites;

    Video(string title, int favorites) : title(title), favorites(favorites) {}
};

class Favorites
{
private:
    queue<Video *> videos;

public:
    Favorites() : videos(){};
    ~Favorites()
    {
        while (!videos.empty())
        {
            videos.pop();
        }
    }

    void addVideo(Video *video)
    {
        videos.push(video);
    }

    void removeVideo()
    {
        if (!videos.empty())
        {
            videos.pop();
        }
        else
        {
            cout << "No videos to remove" << endl;
        }
    }

    void showFavorites()
    {
        while (!videos.empty())
        {
            Video *video = videos.front();
            cout << "Title: " << video->title << " Favorites: " << video->favorites << endl;
            videos.pop();
        }
    }

    void showFirstFavorite()
    {
        if (!videos.empty())
        {
            Video *video = videos.front();
            cout << "Title: " << video->title << " Favorites: " << video->favorites << endl;
        }
        else
        {
            cout << "No videos to show" << endl;
        }
    }

    void showLastFavorite()
    {
        if (!videos.empty())
        {
            Video *video = videos.back();
            cout << "Title: " << video->title << " Favorites: " << video->favorites << endl;
        }
        else
        {
            cout << "No videos to show" << endl;
        }
    }

    int size()
    {
        return videos.size();
    }
};

int main()
{
    Favorites favorites;
    int option;

    while (option != 2)
    {
        string title;
        int favoritesNumber;
        cout << "Enter the title of the video: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter the number of favorites: ";
        cin >> favoritesNumber;
        favorites.addVideo(new Video(title, favoritesNumber));
        cout << "Do you want to add another video? (1. Yes, 2. No): ";
        cin >> option;
    }
    while (option != 2)
    {
        cout << "1. Show first favorite" << endl;
        cout << "2. Show last favorite" << endl;
        cout << "3. Remove video" << endl;
        cout << "4. Show all favorites" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter an option: ";
        cin >> option;
        if (option == 1)
        {
            favorites.showFirstFavorite();
        }
        else if (option == 2)
        {
            favorites.showLastFavorite();
        }
        else if (option == 3)
        {
            favorites.removeVideo();
        }
        else if (option == 4)
        {
            favorites.showFavorites();
        }
        else if (option == 5)
        {
            break;
        }
        else
        {
            cout << "Invalid option" << endl;
        }
    }

    return 0;
}