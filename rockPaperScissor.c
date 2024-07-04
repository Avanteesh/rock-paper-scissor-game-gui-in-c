#include <gtk/gtk.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


enum window { 
 HEIGHT = 400, 
 WIDTH = 600 
};

const char choices[3][7] = { "Rock", "Paper", "Scissor" };
uint64_t choice_count = sizeof(choices)/sizeof(choices[0]);

static uint32_t playerScore = 0;
static uint32_t robotScore = 0;
static uint32_t numberOfGamesLeft = 0;

/* gtk_labels */
GtkWidget *Heading_Label, *Robot_text_label;
GtkWidget *player_text_label, *WinnerText;
GtkWidget *ButtonRock, *ButtonPaper, *ButtonScissor;

uint32_t RobotChoice(uint32_t len)    {
   srand(time(NULL));
   uint32_t randchoice = rand() % len;
   return randchoice;
}

/* check is game is draw */
bool is_draw(const char *playerinput, const char *robotinput)   {
    return (strcmp(playerinput, robotinput) == 0);
}

bool player_won(const char *playerinput, const char *robotinput)    {
    if ((strcmp(playerinput, "Paper") == 0) && (strcmp(robotinput, "Rock") == 0))   {
	return true;
    }
    else if ((strcmp(playerinput, "Scissor") == 0) && (strcmp(robotinput, "Paper") == 0))  {
        return true;
    }
    else if ((strcmp(playerinput, "Rock") == 0) && (strcmp(robotinput, "Scissor") == 0))  {
	return true;
    }

    return false;

}

void putRockOnLabel(void)   {
   gtk_label_set_text(GTK_LABEL(player_text_label), "player - Rock");
   // robot's turn
   uint32_t choiceIndex = RobotChoice(choice_count);
   char robotInput[20], robot_Choice[7];
   strcpy(robot_Choice, choices[choiceIndex]);
   snprintf(robotInput, sizeof(robotInput), "Robot - %s", robot_Choice);
   gtk_label_set_text(GTK_LABEL(Robot_text_label), robotInput);

   if (player_won("Rock", robot_Choice))   {
     gtk_label_set_text(GTK_LABEL(WinnerText), "You won the game!");
   }
   else if (is_draw("Rock", robot_Choice))  {
     gtk_label_set_text(GTK_LABEL(WinnerText), "Its a Draw");
   }
   else {
     gtk_label_set_text(GTK_LABEL(WinnerText), "You loose!");
   }
}

void putPaperOnLabel(void)     {
   gtk_label_set_text(GTK_LABEL(player_text_label), "player - Paper");
   uint32_t choiceIndex = RobotChoice(choice_count);
   char robotInput[20], robot_Choice[7];
   strcpy(robot_Choice, choices[choiceIndex]);
   snprintf(robotInput, sizeof(robotInput), "Robot - %s", robot_Choice);
   gtk_label_set_text(GTK_LABEL(Robot_text_label), robotInput);

   if (player_won("Paper", robot_Choice))   {
     gtk_label_set_text(GTK_LABEL(WinnerText), "You won the game!");
   }
   else if (is_draw("Paper", robot_Choice))  {
     gtk_label_set_text(GTK_LABEL(WinnerText), "Its a Draw");
   }
   else {
     gtk_label_set_text(GTK_LABEL(WinnerText), "You loose!");
   }
}

void putScissorOnLabel(void)   {
   gtk_label_set_text(GTK_LABEL(player_text_label), "player - Scissor");
   uint32_t choiceIndex = RobotChoice(choice_count);
   char robotInput[20], robot_Choice[7];
   strcpy(robot_Choice, choices[choiceIndex]);
   snprintf(robotInput, sizeof(robotInput), "Robot - %s", robot_Choice);
   gtk_label_set_text(GTK_LABEL(Robot_text_label), robotInput);

   if (player_won("Scissor", robot_Choice))   {
     gtk_label_set_text(GTK_LABEL(WinnerText), "You won the game!");
   }
   else if (is_draw("Scissor", robot_Choice))  {
     gtk_label_set_text(GTK_LABEL(WinnerText), "Its a Draw");
   }
   else {
     gtk_label_set_text(GTK_LABEL(WinnerText), "You loose!");
   }
}

int32_t main(int32_t argc, char *argv[])     {

   GtkWidget *window, *grid;
   gtk_init(&argc, &argv);

   enum window win_width = WIDTH, win_height = HEIGHT;
   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_widget_set_size_request(window, win_width, win_height);
   g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
   // create grid
   grid = gtk_grid_new();
   gtk_container_add(GTK_CONTAINER(window), grid);
   GtkWidget *label_margin = gtk_label_new("");
   gtk_grid_attach(GTK_GRID(grid), label_margin, 1, 1, 2, 2);
   //heading
   Heading_Label = gtk_label_new("Rock Paper Scissor Game");
   gtk_grid_attach(GTK_GRID(grid), Heading_Label, 2, 3, 2, 2);

   player_text_label = gtk_label_new("player - ");
   gtk_grid_attach(GTK_GRID(grid), player_text_label, 5, 6, 1, 1);
   Robot_text_label = gtk_label_new("robot: - ");
   gtk_grid_attach(GTK_GRID(grid), Robot_text_label, 5, 8, 1, 1);

   ButtonRock = gtk_button_new_with_label("Rock");
   g_signal_connect(ButtonRock, "clicked", G_CALLBACK(putRockOnLabel), NULL);
   gtk_grid_attach(GTK_GRID(grid), ButtonRock, 3,13, 2, 2);

   ButtonPaper = gtk_button_new_with_label("Paper");
   g_signal_connect(ButtonPaper, "clicked", G_CALLBACK(putPaperOnLabel), NULL);
   gtk_grid_attach(GTK_GRID(grid), ButtonPaper, 5, 13, 2, 2);

   ButtonScissor = gtk_button_new_with_label("Scissor");
   g_signal_connect(ButtonScissor, "clicked", G_CALLBACK(putScissorOnLabel), NULL);
   gtk_grid_attach(GTK_GRID(grid), ButtonScissor, 8, 13, 2, 2);

   WinnerText = gtk_label_new(" ");
   gtk_grid_attach(GTK_GRID(grid), WinnerText, 5, 16, 3, 3);

   gtk_widget_show_all(window);
   gtk_main();

   return 0;
  
}


