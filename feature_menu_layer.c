#include "pebble.h"

#define NUM_MENU_SECTIONS 2
#define NUM_MENU_ICONS 3
#define NUM_FIRST_MENU_ITEMS 20
#define NUM_SECOND_MENU_ITEMS 0

static Window *window;
static char body_text[100];
    static char body_text1[1000];
// This is a menu layer
// You have more control than with a simple menu layer
static MenuLayer *menu_layer;
TextLayer *text_layer;
// Menu items can optionally have an icon drawn with them
static GBitmap *menu_icons[NUM_MENU_ICONS];

static int current_icon = 0;

// You can draw arbitrary things in a menu item such as a background
static GBitmap *menu_background;

// A callback is used to specify the amount of sections of menu items
// With this, you can dynamically add and remove sections
static uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return NUM_MENU_SECTIONS;
}

// Each section has a number of items;  we use a callback to specify this
// You can also dynamically add and remove items using this
static uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  switch (section_index) {
    case 0:
      return NUM_FIRST_MENU_ITEMS;

    case 1:
      return NUM_SECOND_MENU_ITEMS;

    default:
      return 0;
  }
}

// A callback is used to specify the height of the section header
static int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
  // This is a define provided in pebble.h that you may use for the default height
  return MENU_CELL_BASIC_HEADER_HEIGHT;
}

// Here we draw what each header is
static void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  // Determine which section we're working with
  switch (section_index) {
    case 0:
      // Draw title text in the section header
      menu_cell_basic_header_draw(ctx, cell_layer, "First aid guidance using info from red cross");
      break;

   /* case 1:
      menu_cell_basic_header_draw(ctx, cell_layer, "One more");
      break;*/
  }
}

// This is the menu item draw callback where you specify what each item should look like
static void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
  // Determine which section we're going to draw in
  switch (cell_index->section) {
    case 0:
      // Use the row to specify which item we'll draw
      switch (cell_index->row) {
        case 0:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Allergies","Click here", NULL);
          break;
        case 1:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Asthma attack","Click here", NULL);
          break;
        case 2:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Bleeding","Click here", NULL);
          break;
        case 3:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Broken bone","Click here", NULL);
          break;
        case 4:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Burns","Click here", NULL);
          break;
        case 5:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Choking","Click here", NULL);
          break;
        case 6:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Diabetic emergency","Click here", NULL);
          break;
        case 7:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Distress","Click here", NULL);
          break;
        case 8:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Head injury","Click here", NULL);
          break;
        case 9:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Heart attack","Click here", NULL);
          break;
        case 10:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Heat stroke","Click here", NULL);
          break;
        case 11:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Hypothermia","Click here", NULL);
          break;
        case 12:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Meningitis","Click here", NULL);
          break;
        case 13:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Poisoning","Click here", NULL);
          break;
        case 14:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Seizure/Epilepsy","Click here", NULL);
          break;
        case 15:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Stings/bites","Click here", NULL);
          break;
        case 16:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Strains/Sprains","Click here", NULL);
          break;
        case 17:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Stroke","Click here", NULL);
          break;
        case 18:
          // This is a basic menu item with a title and subtitle
          menu_cell_basic_draw(ctx, cell_layer, "Unconscious","Click here", NULL);
          break;
        

        case 19:
          // This is a basic menu icon with a cycling icon
          menu_cell_basic_draw(ctx, cell_layer, "Disclaimer","use only if you agree", NULL);
          break;

       /* case 2:
          // Here we use the graphics context to draw something different
          // In this case, we show a strip of a watchface's background
          graphics_draw_bitmap_in_rect(ctx, menu_background,
              (GRect){ .origin = GPointZero, .size = layer_get_frame((Layer*) cell_layer).size });
          break;*/
      }
      break;

    /*case 1:
      switch (cell_index->row) {
        case 0:
          // There is title draw for something more simple than a basic menu item
          menu_cell_title_draw(ctx, cell_layer, "Disclaimer");
          break;
      }*/
  }
}

// Here we capture when a user selects a menu item
void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
  // Use the row to specify which item will receive the select action
  switch (cell_index->row) {
    // This is the menu item with the cycling icon
    case 0:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"If the person has a known allergy and has an auto-injector/Epi-pen, you can help them to use it. Give them constant reassurance and call 911");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 1:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"Help the person sit in a comfortable position and take their medication. Give them constant reassurance and call 911");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 2:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"Put pressure on the wound with whatever is available to stop or slow down the flow of blood. Call 911 in case.");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 3:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"Encourage the person to support the injury with their hand or use a cushion or item of clothing to prevent unnecessary movement. Call 911 in case.");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 4:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"Cool the burn under cool running water for 10 minutes. Losely cover the burns with plastic wrap if necessary. Call 911 in case.");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 5:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"Hit them firmly on their back between the shoulder blades 5 times to dislodge the object followed by 5 quick abdominal thursts. Call 911 in case.");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 6:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"Give them something containing sugar to eat or a non diet dring. If the person is breathing fast, pale, or sweating, call 911.");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 7:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"Be considerate of what is going on around them and what they need.");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 8:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"If they become confused, drowsy, vomit or if the fall was greater than 2 times their height, Call 911. Ask them to rest and apply cold compress.");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 9:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"The person may have persistent vice-like chest pain, isolated unexplained discomfort in arm, neck, jaw, back or stomach. Give them aspirin if they are not allergic. Call 911");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 10:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"Move the person to a cooler place. Loosen tight clothing. Apply wet cloth or towel to the skin. Give small amound of cool water to drink slowly.");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 11:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"Warm the person slowly. If they are conscious, give them warm drink or soup by mouth. Call 911");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 12:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"Symptoms: Complaint of stiff neck, muscles and joint paint, headache, high temperature and sensitive to light. Call 911");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 13:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"Establish what they have taken, when and how much. Call 911");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 14:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"Do not restrain them. Use something like blanket or cloth next to their head to protect from injury. Do not place under their head. After seizure, help the person to rest on their side with head tilted back");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 15:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"Remove the stinger by scraping it away with a flat surface. Wash the wound with soap and water. Cover with dressing. Apply ice or cold pack. Call 911 in case");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 16:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"Apply ice to the injury. If no improvement, seek medical device.");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 17:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"Think F.A.S.T. Face: is their weakness on one side of the face. Arms: Can they raise both arms. Speech: Is their speech easily understood. Time to call 911");
    text_layer_set_text(text_layer, body_text1);
    break;
    case 18:
    	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"Check breathing by tilting their head backwards and looking and feeling for breaths. If they are not breathing, perform CPR and call 911. If they are breathing, move them onto their side and tilt the head back. Call 911");
    text_layer_set_text(text_layer, body_text1);
    break;

    case 19:
      // Cycle the icon
      	text_layer = text_layer_create(GRect(0, 0, 144, 154));
  
  // Add the text layer to the window
	  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));
    
    //clock_copy_time_string	(body_text,100)	;
    snprintf(body_text1, sizeof(body_text1),"This application is provided only as a guide to first aid. All the information used is directly from the red cross app. I am not responsible for the content or any problems that occur. You cannot sue me in case of problem");
    text_layer_set_text(text_layer, body_text1);
    break;
  }

}

// This initializes the menu upon window load
void window_load(Window *window) {
  // Here we load the bitmap assets
  // resource_init_current_app must be called before all asset loading
  int num_menu_icons = 0;
  menu_icons[num_menu_icons++] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_BIG_WATCH);
  menu_icons[num_menu_icons++] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_SECTOR_WATCH);
  menu_icons[num_menu_icons++] = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MENU_ICON_BINARY_WATCH);

  // And also load the background
  menu_background = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND_BRAINS);

  // Now we prepare to initialize the menu layer
  // We need the bounds to specify the menu layer's viewport size
  // In this case, it'll be the same as the window's
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  // Create the menu layer
  menu_layer = menu_layer_create(bounds);

  // Set all the callbacks for the menu layer
  menu_layer_set_callbacks(menu_layer, NULL, (MenuLayerCallbacks){
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
  });

  // Bind the menu layer's click config provider to the window for interactivity
  menu_layer_set_click_config_onto_window(menu_layer, window);

  // Add it to the window for display
  layer_add_child(window_layer, menu_layer_get_layer(menu_layer));
}

void window_unload(Window *window) {
  // Destroy the menu layer
  menu_layer_destroy(menu_layer);

  // Cleanup the menu icons
  for (int i = 0; i < NUM_MENU_ICONS; i++) {
    gbitmap_destroy(menu_icons[i]);
  }

  // And cleanup the background
  gbitmap_destroy(menu_background);
   text_layer_destroy(text_layer);
}

int main(void) {
  window = window_create();

  // Setup the window handlers
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  window_stack_push(window, true /* Animated */);

  app_event_loop();

  window_destroy(window);
}
